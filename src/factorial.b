declblock{
	int a,b,fac;
}
codeblock{
  a=1;
  fac = 1;
  L1: fac=fac*a;
  	println "factorial(",a,") is: ", fac;
    a=a+1;
    goto L1 if a<10;

}
