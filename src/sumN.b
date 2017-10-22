declblock{
	int data[100];
	int i, sum;
}

codeblock{

	while i < 100 {
		data[i] = i;
		i += 1;
	}
	

	sum = 0;
	i = 0;
	while i< 100 {
		sum = sum + data[i];
		i += 1;
 	}
 	

}

