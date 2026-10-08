# Qin mapper fallback

Apply optional_mapper_probe.patch from frameworks/native before building.
The board uses mapper 2.0 and disables VINTF enforcement during bring-up.
Nonblocking probes of mapper 3/4 let libui reach mapper 2.0.
