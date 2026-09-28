import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Venn diagram / Overlap of Netflix and Amazon Prime users
fig, ax = plt.subplots(figsize=(7, 5))
circle1 = plt.Circle((0.4, 0.5), 0.3, color='#e50914', alpha=0.5, label='Netflix Users (450)')
circle2 = plt.Circle((0.6, 0.5), 0.3, color='#00a8e1', alpha=0.5, label='Amazon Prime Users (300)')

ax.add_patch(circle1)
ax.add_patch(circle2)
ax.set_xlim(0, 1)
ax.set_ylim(0, 1)
ax.set_aspect('equal')
plt.text(0.28, 0.5, "Netflix Only\n300", fontsize=11, fontweight='bold', color='white', ha='center')
plt.text(0.5, 0.5, "Both\n150", fontsize=11, fontweight='bold', color='black', ha='center')
plt.text(0.72, 0.5, "Prime Only\n150", fontsize=11, fontweight='bold', color='white', ha='center')
plt.title('Subscriber Distribution (Netflix vs Amazon Prime)', fontsize=14, fontweight='bold')
plt.axis('off')
plt.legend(loc='lower center')
plt.tight_layout()
plt.savefig('ds_slip_05_q2_streaming.png')
print("[+] Native Venn overlap chart saved as ds_slip_05_q2_streaming.png")
