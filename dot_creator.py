with open("./inputs/bio-grid-mouse.gr") as f:
    lines = f.readlines()

with open("graph.dot", "w") as out:
    out.write("graph G {\n")

    for line in lines:
        if line.startswith("c") or line.startswith("p"):
            continue

        u, v = line.split()
        out.write(f"    {u} -- {v};\n")

    out.write("}\n")
