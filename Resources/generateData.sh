gawk -v"max=$1" 'BEGIN{ print "Xa;Yb;Zc";  srand(systime()); for (a=1; a<max; a++){print int(rand()*54)";" int(rand()*54) ";" int(rand()*54); }}'
