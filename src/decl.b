declblock{
int i = 0;
int x = 2;
}
codeblock{
	println x;
	x = 100;
	println x;
	x = 5;
	println x;
	x = 5;
	while x < 10 {
	x += 1;
	}
	println x;
	if x<10 {
		x = x*x;
	}
	else{
		x += x*x*x;
	}
	x = 5;
	println x;
}
