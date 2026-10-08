def tower_of_hanoi(n, source, target, aux):
    if n == 1:
        print(f"Move disk 1 from {source} to {target}")
        return
    tower_of_hanoi(n - 1, source, aux, target)
    print(f"Move disk {n} from {source} to {target}")
    tower_of_hanoi(n - 1, aux, target, source)

print("\nTower of Hanoi (State Space)\n")
tower_of_hanoi(3, 'A', 'C', 'B')
