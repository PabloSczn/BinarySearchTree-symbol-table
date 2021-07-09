int add ( int a , int b )
{
	return a + b ;
}

int sub ( int c , int d )
{
	return c - d ;
}

int main ( )
{
	int sum = 0 ;
	for ( int i = 1 ; i < 100 ; i ++ )
	{
		add ( sum , i ) ;
	}
	int neg_sum = 0 ;
	for ( int j = 100 ; j > 0 ; j -- )
	{
		sub ( neg_sum , j ) ;
	}
	int result ;
	result = add ( sum , neg_sum ) ;
	if ( result > 0 ) 
	{
		result = result * 100 ;
	}
	long s = 10 ;
	while ( s < result )
	{
		s = s * 2 ;
	}
	if ( s > 1000000 )
	{
		s = s / 2 ;
	}
	long* s_pointer = & s ;
	* s_pointer = * s_pointer - 5 ;
	return 0 ;		
}