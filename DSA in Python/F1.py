
import math
import time
import os

WIDTH, HEIGHT = 90, 32
CHARS = " .:-=+*#%@"

# 3D car model: (x, y, z)
vertices = []
edges = []

def add_box(x1, y1, z1, x2, y2, z2):
    start = len(vertices)
    vertices.extend([
        (x1, y1, z1), (x2, y1, z1),
        (x2, y2, z1), (x1, y2, z1),
        (x1, y1, z2), (x2, y1, z2),
        (x2, y2, z2), (x1, y2, z2)
    ])

    for a, b in [
        (0,1), (1,2), (2,3), (3,0),
        (4,5), (5,6), (6,7), (7,4),
        (0,4), (1,5), (2,6), (3,7)
    ]:
        edges.append((start+a, start+b))

def add_wheel(cx, cy, cz, radius=0.65):
    start = len(vertices)
    segments = 12

    # Two circular rings on each wheel
    for x in [cx - 0.22, cx + 0.22]:
        for i in range(segments):
            angle = 2 * math.pi * i / segments
            vertices.append((
                x,
                cy + radius * math.cos(angle),
                cz + radius * math.sin(angle)
            ))

    for i in range(segments):
        j = (i + 1) % segments
        edges.append((start+i, start+j))
        edges.append((start+segments+i, start+segments+j))
        edges.append((start+i, start+segments+i))

# Main chassis
add_box(-0.45, -0.25, -1.5, 0.45, 0.05, 1.5)

# Front and rear wings
add_box(-1.25, -0.25, 1.45, 1.25, -0.12, 1.7)
add_box(-1.0, 0.0, -1.8, 1.0, 0.2, -1.65)

# Nose cone, made from two rectangular sections
start = len(vertices)
vertices.extend([
    (-0.45, -0.22, 0.8), (0.45, -0.22, 0.8),
    (0.45, 0.0, 0.8), (-0.45, 0.0, 0.8),
    (-0.12, -0.15, 2.0), (0.12, -0.15, 2.0),
    (0.12, -0.05, 2.0), (-0.12, -0.05, 2.0)
])
for a, b in [
    (0,1),(1,2),(2,3),(3,0),
    (4,5),(5,6),(6,7),(7,4),
    (0,4),(1,5),(2,6),(3,7)
]:
    edges.append((start+a, start+b))

# Cockpit
add_box(-0.3, 0.05, -0.45, 0.3, 0.45, 0.45)

# Four wheels
for x in [-0.85, 0.85]:
    for z in [-1.2, 1.15]:
        add_wheel(x, -0.3, z)

def rotate(point, angle):
    x, y, z = point

    # Rotate around the vertical Y axis
    x2 = x * math.cos(angle) - z * math.sin(angle)
    z2 = x * math.sin(angle) + z * math.cos(angle)

    # Slight rotation around X for a better view
    y2 = y * math.cos(0.18) - z2 * math.sin(0.18)
    z3 = y * math.sin(0.18) + z2 * math.cos(0.18)

    return x2, y2, z3

def project(point):
    x, y, z = point
    distance = 6
    scale = 18 / (distance + z)

    screen_x = int(WIDTH / 2 + x * scale)
    screen_y = int(HEIGHT / 2 - y * scale)
    return screen_x, screen_y

def draw_line(canvas, p1, p2):
    x1, y1 = p1
    x2, y2 = p2

    steps = max(abs(x2-x1), abs(y2-y1), 1)

    for i in range(steps + 1):
        t = i / steps
        x = round(x1 + (x2-x1) * t)
        y = round(y1 + (y2-y1) * t)

        if 0 <= x < WIDTH and 0 <= y < HEIGHT:
            canvas[y][x] = "#"

angle = 0

try:
    while True:
        canvas = [[" "] * WIDTH for _ in range(HEIGHT)]

        rotated = [rotate(v, angle) for v in vertices]
        projected = [project(v) for v in rotated]

        for a, b in edges:
            draw_line(canvas, projected[a], projected[b])

        # Draw the terminal frame
        os.system("cls" if os.name == "nt" else "clear")
        print("\033[91m")  # Red text
        print("\n".join("".join(row) for row in canvas))
        print("\033[0m")
        print("       FORMULA 1 | 3D ASCII ENGINE")
        print("       Rotating chassis...  Ctrl+C to exit")

        angle += 0.07
        time.sleep(0.045)

except KeyboardInterrupt:
    print("\nF1 simulation stopped.")
