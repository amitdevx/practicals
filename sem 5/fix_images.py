import os

images_321 = {
    1: [0, 1],
    2: [2],
    3: [3, 4],
    4: [5],
    5: [6],
    6: [7],
    7: [8, 9],
    14: [10],
    15: [11],
    16: [12],
    17: [13],
    18: [14],
    21: [15, 16],
    23: [17],
    24: [18],
    25: [19, 20]
}

images_306 = {
    1: [0],
    2: [1]
}

base_dir = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"

def insert_images(subject_dir, prefix, mapping, ext_map=None):
    for slip, imgs in mapping.items():
        md_path = os.path.join(base_dir, subject_dir, f"Slip_{slip:02d}", f"Slip_{slip:02d}.md")
        if not os.path.exists(md_path):
            continue
            
        with open(md_path, 'r') as f:
            lines = f.read().split('\n')
            
        # Find where to insert (before Viva)
        insert_idx = len(lines)
        for i, line in enumerate(lines):
            if "Viva" in line or "Q3" in line or "Q.3" in line:
                insert_idx = i
                break
                
        img_mds = []
        for img_num in imgs:
            ext = "jpg"
            if ext_map and img_num in ext_map:
                ext = ext_map[img_num]
            img_mds.append(f"![Image](../../../images/{prefix}-{img_num:03d}.{ext})\n")
            
        lines = lines[:insert_idx] + img_mds + lines[insert_idx:]
        
        with open(md_path, 'w') as f:
            f.write('\n'.join(lines))

ext_map_321 = {8: "ppm"}
insert_images("CS-321 Foundation of AI and ML", "CS-321", images_321, ext_map_321)
insert_images("CS-306 Core Java and Web Technology", "CS-306", images_306)

print("Images inserted.")

