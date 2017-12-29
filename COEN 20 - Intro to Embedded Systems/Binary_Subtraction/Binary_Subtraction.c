void SubBinary(int a[8], int b[8], int c[8])    //Nicholas Fong COEN 20 Lab 5 Lewis
	{
// Insert your code here ...        c = a - b
        int i;
        int carry = 0;
        int sum;
        for(i = 0; i < 8; i++){
            sum = a[i] - b[i] - carry;
            if(sum == 1){
                c[i] = 1;
                carry = 0;
            }
            else if(sum == 0){
                c[i] = 0;
                carry = 0;
            }
            else if(sum == -1){
                c[i] = 1;
                carry = 1;
            }
            else if(sum == -2){
                c[i] = 0;
                carry = 1;
            }
        }
	}


