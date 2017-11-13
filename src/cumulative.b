declblock{
	int sum,cumsum[100],arr[100],temp;
  int i,j,prevval;
}
codeblock{
  sum=0;
  i=0;
  while i<=10{
    arr[i]=i;
    i=i+1;
  }
  i=0;
  print "initial array is: ";
  while i<=10{
    print arr[i], " ";
    i = i + 1;
  }
  i = 0;
  println "";
  print "cumulative sum array is: ";
  while i<=10
  {
    cumsum[i]=cumsum[i-1]+arr[i];
    print cumsum[i], " ";
    i=i+1;
  }
  println "";
}
