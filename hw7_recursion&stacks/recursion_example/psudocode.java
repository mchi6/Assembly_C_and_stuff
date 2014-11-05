int math(int x) {
	int i = 0;

	if (x == 0) {
		return 1;
	} else {
		i = math(x - 1);
		return 2i;
	}
}