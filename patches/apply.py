#!/usr/bin/env python3
"""Check and apply the Qin LOS19.1 platform patch series."""
import argparse
from pathlib import Path
import subprocess
import sys


def main():
    patch_dir = Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=patch_dir.parent.parents[2],
                        help='LineageOS source root (defaults to device tree location)')
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    root = args.root.resolve()
    pending = []
    for line in (patch_dir / 'series').read_text().splitlines():
        if not line.strip() or line.lstrip().startswith('#'):
            continue
        repo_name, patch_name = line.split()
        repo = root / repo_name
        patch = patch_dir / patch_name
        if not repo.is_dir() or not patch.is_file():
            raise RuntimeError('Missing repository or patch: ' + line)
        command = ['git', '-C', str(repo), 'apply']
        # The imported audio shim has CRLF locally; ignore whitespace only
        # while recognizing an already-applied patch, never when applying it.
        reverse = subprocess.run(command + ['--reverse', '--ignore-space-change',
                                            '--check', str(patch)],
                                 stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if reverse.returncode == 0:
            print('Already applied:', line)
            continue
        forward = subprocess.run(command + ['--check', str(patch)],
                                 stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if forward.returncode:
            raise RuntimeError('Patch does not apply cleanly: ' + line + '\n' + forward.stderr)
        pending.append((command, patch, line))
        print('Ready:', line)
    if args.dry_run:
        print('Patch series verified;', len(pending), 'pending')
        return
    for command, patch, line in pending:
        subprocess.run(command + [str(patch)], check=True)
        print('Applied:', line)
    print('Qin platform patches complete')


if __name__ == '__main__':
    try:
        main()
    except (RuntimeError, subprocess.CalledProcessError) as error:
        print(error, file=sys.stderr)
        sys.exit(1)
