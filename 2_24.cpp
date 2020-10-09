#include <iostream>

class c_matrix
{
private:
    struct arrays
    {
        int *AD; // [N] Array for diagonal
        int *AU; // [NZ] Array of elements above the diagonal (line by line, top to bottom)
        int *AL; // [NZ] Array of elements below the diagonal (column by column, from left to right)
        int *LJ; // [NZ] Column numbers of elements stored in matrix AU or rows stored in matrix AL
        int *LI; // [N] The location of the first element of every row in AU or every column in AL
    } arr;

    int N; // Array size =  N * N
    int NZ; // Number of non-zero elements / 2
    
public:
    /**
     * @brief Class constructor with parameters
     * @param _N Array size (full)
     * @param _NZ Array size (non-zero elements)
     * 
     * We create arrays for further use by the matrix. 
     * The values of _N and _NZ are obtained at the input.
    */
    c_matrix( int _N, int _NZ ) 
    {  
        N = _N;
        NZ = _NZ;

        arr.AD = new int[ _N ];
        arr.AU = new int[ _NZ ];
        arr.AL = new int[ _NZ ];
        arr.LJ = new int[ _NZ ];
        arr.LI = new int[ _N ];
    }

    /**
     * @brief Destructor of a matrix
     * 
     * We delete the arrays for which the memory was allocated.
    */
    ~c_matrix() 
    {
        delete[] arr.AD;
        delete[] arr.AU;
        delete[] arr.AL;
        delete[] arr.LJ;
        delete[] arr.LI;
    }

    /**
     * @param _matrix The original matrix where the data comes from
     * 
     * Populating AD array.
    */
    void set_AD( int **_matrix )
    {
        for( int i = 0; i < N; ++i )
            arr.AD[ i ] = _matrix[ i ][ i ];
    }

    /**
     * @param _matrix The original matrix where the data comes from
     * 
     * Populating AU array.
    */
    void set_AU( int **_matrix )
    {
        int k = 0;
        for( int i = 0; i < N; ++i )
            for( int j = 0; j < N; ++j )
                if( j > i && _matrix[ i ][ j ] != 0 )
                    arr.AU[ k++ ] = _matrix[ i ][ j ];
    }

    /**
     * @param _matrix The original matrix where the data comes from
     * 
     * Populating AL array.
    */
    void set_AL( int **_matrix )
    {
        int k = 0;
        for( int i = 0; i < N; ++i )
            for( int j = 0; j < N; ++j )
                if( j < i && _matrix[ i ][ j ] != 0 )
                    arr.AL[ k++ ] = _matrix[ i ][ j ];
    }

    /**
     * @param _matrix The original matrix where the data comes from
     * 
     * Populating LJ array.
    */
    void set_LJ( int **_matrix )
    {
        int k = 0;
        for( int i = 0; i < N; ++i )
            for( int j = 0; j < N; ++j )
                if( j > i && _matrix[ i ][ j ] != 0 )
                    arr.LJ[ k++ ] = j + 1;
    }

    /**
     * @param _matrix The original matrix where the data comes from
     * 
     * Populating LI array.
    */
    void set_LI( int **_matrix )
    {
        int k = 1;
        for( int i = 0; i < N; ++i )
        {
            arr.LI[ i ] = k;
            for( int j = 0; j < N; ++j )
                if( j > i && _matrix[ j ][ i ] != 0 )
                    k++;
        }
    }

    /**
     * Displaying the elements of the diagonal.
    */
    void print_AD()
    {
        std::cout << "[AD]: ";

        for( int i = 0; i < N; ++i )
            std::cout << arr.AD[ i ] << " ";
        
        std::cout << std::endl;
    }

    /**
     * Displaying elements above the diagonal.
    */
    void print_AU()
    {
        std::cout << "[AU]: ";

        for( int i = 0; i < NZ; ++i )
            std::cout << arr.AU[ i ] << " ";

        std::cout << std::endl;
    }

    /**
     * Displaying elements under the diagonal.
    */
    void print_AL()
    {
        std::cout << "[AL]: ";

        for( int i = 0; i < NZ; ++i )
            std::cout << arr.AL[ i ] << " ";

        std::cout << std::endl;
    }

    /**
     * Display the column numbers of elements
     * stored in the matrix AU.
    */
    void print_LJ()
    {
        std::cout << "[LJ]: ";

        for( int i = 0; i < NZ; ++i )
            std::cout << arr.LJ[ i ] << " ";

        std::cout << std::endl;
    }

    /**
     * Displaying the location of the first element 
     * of each row in AU.
    */
    void print_LI()
    {
        std::cout << "[LI]: ";

        for( int i = 0; i < N; ++i )
            std::cout << arr.LI[ i ] << " ";

        std::cout << std::endl;
    }

    /**
     * @param i Line number
     * @param j Column number
     * 
     * Getting / Modifying Matrix Elements.
    */
    int &get( int i, int j )
    {
        int value = 0;
        int N1 = 0, N2 = 0;

        if( i == j ) // Diagonal
            /*value =*/return arr.AD[ i ];
        else if( i < j ) // Upper triangle
        {
            N1 = arr.LI[ i ];
            N2 = arr.LI[ i + 1 ];
            int temp = 0;

            for( int k = N1; k < N2; ++k )
            {
                if( arr.LJ[ k - 1 ] == ( j + 1 ) )
                {
                    return /*value =*/ arr.AU[ k - 1 ];
                    break;
                }
            }
        }
        else if( i > j ) // Lower triangle
        {
            N1 = arr.LI[ j ];
            N2 = arr.LI[ j + 1 ];
            int temp = 0;

            for( int k = N1; k < N2; ++k )
            {
                if( arr.LJ[ k - 1 ] == ( i + 1 ) )
                {
                    return /*value =*/ arr.AL[ k - 1 ];
                    break;
                }
            }
        }

        // It shouldn't get here. Only because of mcvs need to return smth.
        return value;
    }
};

/**
 * @return pseudo-rand number in a certain range
 * 
 * We generate and display a pseudo-random number in a certain range
*/
unsigned int pseudo_rand()
{
    // Start number - 1234
    static unsigned int seed = 1234;
 
    // We take the starting number and, with its help, generate a new value
    seed = (8243729 * seed + 2394403);
 
    // return a value between 0 and 6
    return seed % 7;
}

/**
 * @param _matrix The original matrix where the data comes from
 * @param _N Full size of the array
 * 
 * Displaying the matrix (initial).
*/
void out_matrix( int **_matrix, int _N )
{
    for( int i = 0; i < _N; ++i )
    {
        for( int j = 0; j < _N; ++j )
        {
            std::cout << _matrix[ i ][ j ] << " ";
        }
        std::cout << std::endl;
    }
}

int main( void )
{
    int N = 0; // Array size N * N
    int NZ = 0; // Number of non-zero elements in a triangle (above / below the diagonal)

    std::cout << "Enter size of matrix ( N ): ";

    // Get 'N' & Check that only numbers are entered
    while( !( std::cin >> N ) || std::cin.peek() != '\n' )
    {
        std::cin.clear();
        while( std::cin.get() != '\n');
        std::cout << "Allowed only numbers!" << std::endl;;
    }

    // Creating N * N matrix
    int **array = new int*[ N ];
    for( int i = 0; i < N; ++i ) 
        array[ i ] = new int[ N ];

    // Filling the matrix with PRNG
    for( int i = 0; i < N; ++i )
        for( int j = 0; j < N; ++j )
            /*std::cin >> array[ i ][ j ];//*/array[ i ][ j ] = pseudo_rand();

    // Symmetry conditions
    for( int i = 0; i < N; ++i )
        for( int j = 0; j < N; ++j )
            if( array[ i ][ j ] == 0 )
                array[ j ][ i ] = 0;

    // Output the ready array for the matrix
    out_matrix( array, N );

    // Get the number of nonzero elements in total and on the diagonal
    int diagonal_not_zeros = 0;
    int all_not_zeros = 0;

    for( int i = 0; i < N; ++i )
    {
        for( int j = 0; j < N; ++j )
            if( array[ i ][ j ] != 0 )
                all_not_zeros++;
        
        // Non-zero elements on the diagonal
        if( array[ i ][ i ] == 0 )
            diagonal_not_zeros++;
    }

    // Get count of non-zero elements
    NZ = ( all_not_zeros - diagonal_not_zeros ) / 2;

    std::cout << "===============" << std::endl;
    std::cout << "[NZ]: " << NZ << " | [N]: " << N << std::endl;

    // Create a matrix
    c_matrix matrix( N, NZ );

    // Filling matrix arrays
    matrix.set_AD( array );
    matrix.set_AU( array );
    matrix.set_AL( array );
    matrix.set_LJ( array );
    matrix.set_LI( array );

    // Display elements of matrix arrays
    matrix.print_AD(); 
    matrix.print_AU(); 
    matrix.print_AL();
    matrix.print_LJ();
    matrix.print_LI();

    std::cout << "===============" << std::endl;

    int b = 0;
    std::cout << "Enter some number (b): ";

    // Get 'b' & Check that only numbers are entered
    while( !( std::cin >> b ) || std::cin.peek() != '\n' )
    {
        std::cin.clear();
        while( std::cin.get() != '\n');
        std::cout << "Allowed only numbers!" << std::endl;;
    }

    /* At the beginning more b, then less b */
    for( int i = 0; i < N; ++i )
    {
        for( int j = 0; j < N; ++j )
        {
            if( matrix.get( i, j ) == 0 ) // Only non-zero elements are allowed
                continue;

            // Element less than b?
            if( matrix.get( i, j ) <= b )
            {
                // Looking for the next element greater than b
                for( int l = i; l < N; ++l )
                {
                    for( int k = 0; k < N; ++k )
                    {
                        // We will not compare elements that have already passed at the beginning or zero elements
                        if ( l == i && k <= j || matrix.get( l, k ) == 0 )
							continue;

                        // The current element is greater than b?
						if ( matrix.get( l, k ) > b ) 
						{
                            // Debug shit
							std::cout << "[SWAP]: " << matrix.get( i, j ) << " on " << matrix.get( l, k ) << std::endl;

                            // Swapping
							int temp = matrix.get( i, j );
							matrix.get( i, j ) = matrix.get( l, k );
							matrix.get( l, k ) = temp;

                            // Back to the initial cycle
							goto back;
						}
                    }
                }
            }

            // Return point from loops..
            back:;
        }
    }

    std::cout << "===============" << std::endl;
    std::cout << "After swapping: " << std::endl;

    // Displaying the final matrix
    for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << matrix.get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

    return EXIT_SUCCESS;
}