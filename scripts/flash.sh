#!/usr/bin/env bash
# Downloads the latest CI-built Lily58 firmware (GitHub Actions artifact
# "lily58-firmware") and walks you through flashing both halves.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

command -v gh >/dev/null || { echo "gh (GitHub CLI) is required. Try: nix-shell -p gh" >&2; exit 1; }
command -v lsblk >/dev/null || { echo "lsblk is required (util-linux)." >&2; exit 1; }

WORKDIR="$(mktemp -d)"
trap 'rm -rf "$WORKDIR"' EXIT

echo "==> Checking latest build..."
IFS=$'\t' read -r RUN_ID STATUS CONCLUSION HEAD_SHA < <(
  gh run list --workflow=build.yml --limit=1 \
    --json databaseId,status,conclusion,headSha \
    --jq '.[0] | [.databaseId, .status, .conclusion, .headSha] | @tsv'
)

if [[ -z "${RUN_ID:-}" ]]; then
  echo "No workflow runs found (see gh output above, if any)." >&2
  exit 1
fi
if [[ "$STATUS" != "completed" ]]; then
  echo "Latest run is still '$STATUS'. Wait for it: gh run watch $RUN_ID" >&2
  exit 1
fi
if [[ "$CONCLUSION" != "success" ]]; then
  echo "Latest run did not succeed (conclusion: $CONCLUSION): gh run view $RUN_ID" >&2
  exit 1
fi

LOCAL_SHA="$(git rev-parse HEAD)"
if [[ "$HEAD_SHA" != "$LOCAL_SHA" ]]; then
  echo "Note: latest build is for commit ${HEAD_SHA:0:8}, local HEAD is ${LOCAL_SHA:0:8}." >&2
fi

echo "==> Downloading firmware (run $RUN_ID)..."
gh run download "$RUN_ID" --name lily58-firmware --dir "$WORKDIR"

LEFT_UF2="$WORKDIR/lily58_left.uf2"
RIGHT_UF2="$WORKDIR/lily58_right.uf2"
for f in "$LEFT_UF2" "$RIGHT_UF2"; do
  [[ -f "$f" ]] || { echo "Missing expected firmware file: $f" >&2; exit 1; }
done

# Fallback mount point, used only if nothing auto-mounts the drive (no
# udisksctl/udevil/pmount on this system) — needs sudo.
FALLBACK_MOUNT="/tmp/lily58-flash"

# Finds the RP2040 bootloader drive by its RPI-RP2 filesystem label.
# Uses `lsblk -P` (KEY="value" pairs) instead of raw/list mode: raw mode
# drops empty fields, which shifts columns when MOUNTPOINT is empty.
find_bootloader() {
  local line mnt dev
  line="$(lsblk -Pno LABEL,MOUNTPOINT,PATH 2>/dev/null | grep '^LABEL="RPI-RP2"' | head -1)"
  [[ -z "$line" ]] && return 1
  mnt="$(grep -o 'MOUNTPOINT="[^"]*"' <<<"$line" | cut -d'"' -f2)"
  dev="$(grep -o 'PATH="[^"]*"' <<<"$line" | cut -d'"' -f2)"

  if [[ -n "$mnt" ]]; then
    printf '%s\n' "$mnt"
    return 0
  fi
  [[ -z "$dev" ]] && return 1

  if command -v udisksctl >/dev/null; then
    udisksctl mount -b "$dev" --no-user-interaction >/dev/null 2>&1 || true
    mnt="$(lsblk -no MOUNTPOINT "$dev" 2>/dev/null)"
    if [[ -n "$mnt" ]]; then
      printf '%s\n' "$mnt"
      return 0
    fi
  fi

  # No auto-mounter available: mount it ourselves.
  mkdir -p "$FALLBACK_MOUNT"
  if sudo mount -o "uid=$(id -u),gid=$(id -g)" "$dev" "$FALLBACK_MOUNT" 2>/dev/null; then
    printf '%s\n' "$FALLBACK_MOUNT"
    return 0
  fi
  return 1
}

wait_for_bootloader() {
  local timeout=30 waited=0 mnt
  while (( waited < timeout )); do
    if mnt="$(find_bootloader)"; then
      printf '%s\n' "$mnt"
      return 0
    fi
    sleep 1
    ((waited++))
  done
  return 1
}

flash_half() {
  local name="$1" uf2="$2" mnt
  echo
  echo "=== $name half ==="
  read -rp "Connect the $name half via USB (TRRS unplugged), double-tap reset, then press Enter: " _
  echo "Waiting for the RPI-RP2 drive..."
  if ! mnt="$(wait_for_bootloader)"; then
    echo "Timed out waiting for the bootloader drive. Is it in bootloader mode?" >&2
    exit 1
  fi
  echo "Found $mnt — copying firmware..."
  cp "$uf2" "$mnt/"
  sync
  if [[ "$mnt" == "$FALLBACK_MOUNT" ]]; then
    sudo umount "$mnt" 2>/dev/null || true
  fi
  echo "$name half flashed."
}

flash_half "LEFT" "$LEFT_UF2"
flash_half "RIGHT" "$RIGHT_UF2"

echo
echo "Both halves flashed. Reconnect the TRRS cable (USB unplugged first), then load the saved .vil in Vial if the remaps reset."
