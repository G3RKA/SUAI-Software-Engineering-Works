import sys
import numpy as np
from PIL import Image

src, dst = sys.argv[1:3]
h = np.asarray(Image.open(src)).astype(np.float64) / 65535
n = h.shape[0]
# плавный спад высоты до нуля у краёв карты
t = np.clip(np.minimum(np.arange(n), np.arange(n)[::-1]) / (0.15 * n), 0, 1)
w = t * t * (3 - 2 * t)
h *= w[:, None] * w[None, :]
Image.fromarray((h * 65535).astype(np.uint16)).save(dst)