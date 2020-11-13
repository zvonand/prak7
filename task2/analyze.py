result = {}

with open("res.log") as f:
    l = f.readline()
    while l:
        c = l.split()
        if not c or c[0] != "tasks:":
            l = f.readline()
            continue
        tasks_procs = (c[1], c[3])

        sum_time, sum_dev = 0, 0
        for i in range(3):
            c = f.readline().split()
            sum_time += int(c[0])
            sum_dev += float(c[1])
        result[tasks_procs] = (sum_time // 3, sum_dev // 3)
        l = f.readline()

with open("avg.log", "w") as f:
    for key in result.keys():
        f.write(f"nTasks: {key[0]}, nProcs: {key[1]}\nAvg_runtime: {result[key][0]}, Avg_deviation: {int(result[key][1])}%\n\n")
