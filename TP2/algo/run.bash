echo "algo,serie,taille,temps,distance" > ./results.csv

ex_folder="../data"

for algo in "progdyn"; do
    for ex in $(ls ${ex_folder}/dp); do
        size=$(echo $ex | cut -d_ -f2)
        t=$(./tp.sh -e ${ex_folder}/dp/${ex} -a $algo -t)
        d=$(./tp.sh -e ${ex_folder}/dp/${ex} -a $algo -d)
        echo $algo,"dp",$size,$t,$d
    done
done >> results.csv

for algo in "glouton" "approx"; do
    for testset_folder in $(ls $ex_folder); do
        for ex in $(ls ${ex_folder}/${testset_folder}); do
            size=$(echo $ex)
            t=$(./tp.sh -e ${ex_folder}/${testset_folder}/${ex} -a $algo -t)
            d=$(./tp.sh -e ${ex_folder}/${testset_folder}/${ex} -a $algo -d)
            echo $algo,$testset_folder,$size,$t,$d
        done
    done
done >> results.csv
