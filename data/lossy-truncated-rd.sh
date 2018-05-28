original_size=`wc -c < $1`

count=1
while [ $count -le 1500 ]; do
    (kdu_compress Clayers=$2 -i $1 -o 1.jp2 >&2) 2> /dev/null
    dd if=1.jp2 of=2.jp2 bs=100 count=$count 
    (kdu_expand -i 2.jp2 -o 1.pgm >&2) 2> /dev/null
    compressed_size=`wc -c < 2.jp2`
    bpp=`echo "$compressed_size/$original_size*8" | bc -l`
    echo -n $bpp " "
    mse=`snr --file_A=$1 --file_B=1.pgm | grep RMSE | cut -d " " -f 3`
    echo $mse
    let count=count+1
    (echo $count >&2)
done