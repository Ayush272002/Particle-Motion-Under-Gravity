from particle import Particle
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, FFMpegWriter

p = Particle(x=1.0, y=10.0, vx=0.1, vy=0.0)
dt = 0.01
steps = 500

fig, ax = plt.subplots()
ax.set_xlim(0, 5)
ax.set_ylim(0, 12)
point, = ax.plot([p.x], [p.y], 'o', markersize=15)

def update(frame):
    p.step(dt)
    point.set_data([p.x], [p.y])
    return point,

anim = FuncAnimation(fig, update, frames=steps, interval=10)

writer = FFMpegWriter(fps=60)
anim.save("particle_bounce.mp4", writer=writer)
