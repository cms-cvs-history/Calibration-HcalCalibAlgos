for i in $(seq 11 500); do

echo ' Job ' ${i}

#bsub -q cmscaf1nh batchjob_calib_valid.csh ${i} 

bsub -q cmscaf1nh batchjob_analisotrk.csh ${i} 

#bsub -q 1nh batchjob_calib_valid.csh ${i} 

done 