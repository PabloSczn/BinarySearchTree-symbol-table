int string_length ( char* str )
{
	int len = 0 ;
	while ( * ( str + len ) != '\0' )
	{
		len ++ ;
	}
	return len ;
}
	
void chomp ( char* str )
{ 
	int len = string_length ( str ) ;
	if ( len > 0 && * ( str + len - 1 ) == '\n' )
	{
		* ( str + len - 1 ) = '\0' ;
	}
}

int main ( )
{
	char name [] = "Neil\n" ;
	int len = string_length ( name ) ;
	if ( len >= 3 )
	{
		chomp ( name ) ;
	}
	return 0 ;
}