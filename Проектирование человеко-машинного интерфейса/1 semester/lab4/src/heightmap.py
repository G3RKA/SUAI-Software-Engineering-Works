import sys
import numpy as np
from PIL import Image

out = sys.argv[1]
N = 1024
rng = np.random.default_rng(4331)


def smooth_noise(res):
    g = rng.random((res + 1, res + 1))
    x = np.linspace(0, res, N, endpoint=False)
    i = x.astype(int)
    t = x - i
    t = t * t * (3 - 2 * t)
    a = g[i][:, i]
    b = g[i][:, i + 1]
    c = g[i + 1][:, i]
    d = g[i + 1][:, i + 1]
    tx = t[None, :]
    ty = t[:, None]
    return (a * (1 - tx) + b * tx) * (1 - ty) + (c * (1 - tx) + d * tx) * ty


h = np.zeros((N, N))
amp = 1.0
for octave in range(7):
    h += amp * smooth_noise(4 * 2 ** octave)
    amp *= 0.5
h = (h - h.min()) / (h.max() - h.min())

# Горный хребет по диагонали и спад к краям
yy, xx = np.mgrid[0:1:N * 1j, 0:1:N * 1j]
ridge = np.exp(-((xx - yy * 0.8 - 0.1) ** 2) / 0.02)
edge = np.clip(1.3 - 1.6 * np.hypot(xx - 0.5, yy - 0.5), 0, 1)
h = (0.55 * h + 0.45 * ridge * h ** 0.7) * edge
h = h ** 1.4
h = (h - h.min()) / (h.max() - h.min())

Image.fromarray((h * 65535).astype(np.uint16)).save(out)
Image.fromarray((h * 255).astype(np.uint8)).save(out.replace('.png', '_preview.png'))
