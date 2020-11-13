echo "Elapsed time: | Deviation: | " > res.log

for threads in 1 2 3 4 6 8 12 16
do
  for ntasks in 50000 100000 150000 200000
  do
    for nprocs in 10 25 50
    do
      ./ParamsGenerator/build/ParamsGenerator $nprocs $ntasks 1 100
      echo "threads: $threads tasks: $ntasks procs: $nprocs " >> res.log
      echo "threads: $threads tasks: $ntasks procs: $nprocs "
      ./cmake-build-debug/task2 $threads >> res.log
    echo ""  >> res.log
    done
  done
done