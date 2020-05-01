/**
* @brief
*		Find errors and decrease probability of getting errors of the same kind in the future
*		This piece of code won't compile and it doesn't describe an entire algorithm: just part of some page storage
*
* @author
*		AnnaM
*/

// ========================================
// BUG 1
// ========================================

/*
Wrong header name
it is supposed to be 
#include <windows.h>
and probably (but not sure)
it is necessary to
#include <string.h>
to use memset()
*/

// ========================================

#include <windows.h>
#include <stdio.h>
#include <string.h>

enum PAGE_COLOR
{
	PG_COLOR_GREEN = 1, /* page may be released without high overhead */
	PG_COLOR_YELLOW, /* nice to have */
	PG_COLOR_RED	/* page is actively used */
};

// ========================================
// BUG 1
// ========================================

/*
No operator to cast from PageKey to int
for the further comparison
*/

// ========================================

// ========================================
// BUG 1
// ========================================

/*
No default constructor
and constructor with param int 
*/

// ========================================


/**
 * UINT Key of a page in hash-table (prepared from color and address)
 */
union PageKey
{
	struct
	{
        char	cColor: 8;
		int	cAddr: 24;
	};
	operator int() const {
    	return (cColor << 24) + cAddr;
    }
    PageKey(int a):
    	cColor(a >> 24),
    	cAddr(a - (cColor << 24))
    { }
    PageKey():
    	cColor(0),
    	cAddr(0)
    {}

	int	uKey;
};

// ========================================
// BUG 1
// ========================================

/*
Bitwise operations with pointers
*/

// ========================================

/* Prepare from 2 chars the key of the same configuration as in PageKey */
#define CALC_PAGE_KEY( Addr, Color )	(  (Color) + (*Addr) << 8 ) 


/**
 * Descriptor of a single guest physical page
 */
struct PageDesc
{
	PageKey			uKey;	

	/* list support */
	PageDesc		*next, *prev;
};

#define PAGE_INIT( Desc, Addr, Color )              \
    {                                               \
        (Desc).uKey = CALC_PAGE_KEY( Addr, Color ); \
        (Desc).next = (Desc).prev = NULL;           \
    }
        

/* storage for pages of all colors */
static PageDesc* PageStrg[ 3 ];

void PageStrgInit()
{
	memset( PageStrg, 0, sizeof(&PageStrg) );
}



// ========================================
// BUG 1
// ========================================

/*
Column after for loop
*/

// ========================================

PageDesc* PageFind( void* ptr, char color )
{
	for( PageDesc* Pg = PageStrg[color]; Pg; Pg = Pg->next )
        if( Pg->uKey == CALC_PAGE_KEY(ptr,color) )
           return Pg;                                                                                                                                     
    return NULL;
}

// ========================================
// BUG 4
// ========================================

/*
PageRemove function
is not defined
*/

// ========================================

// ========================================
// BUG 4
// ========================================

/*
No return statement
*/

// ========================================

PageDesc* PageReclaim( UINT cnt )
{
	UINT color = 0;
	PageDesc* Pg;
	while( cnt )
	{
		Pg = Pg->next;
		PageRemove( PageStrg[ color ] );
		cnt--;
		if( Pg == NULL )
		{
			color++;
			Pg = PageStrg[ color ];
		}
	}
}


// ========================================
// BUG 2
// ========================================

/*
pg is a pointer
it should be passsed as *pg
to be used as value
*/

// ========================================

// ========================================
// BUG 3
// ========================================

/*
Macro expansion 
should be surrounded by brackets
*/

// ========================================
            
PageDesc* PageInit( void* ptr, UINT color )
{
    PageDesc* pg = new PageDesc;
    if( pg )
    {
    	PAGE_INIT(pg, ptr, color);
    }
    else
        printf("Allocation has failed\n");
    return pg;
}

/**
 * Print all mapped pages
 */

// ========================================
// BUG 3
// ========================================

/*
Assignment instead of comparison
*/

// ========================================

// ========================================
// BUG 3
// ========================================

/*
Address uAddr is not defined in structure
*/

// ========================================

// ========================================
// BUG 4
// ========================================

/*
ISO C++ forbids converting a string constant to ‘char*’
Const added 
*/

// ========================================
void PageDump()
{
	int color = 0;
	#define PG_COLOR_NAME(clr) #clr
	char* PgColorName[] = 
	{
		PG_COLOR_NAME(PG_COLOR_RED),
		PG_COLOR_NAME(PG_COLOR_YELLOW),
		PG_COLOR_NAME(PG_COLOR_GREEN)
	};

	while( color <= PG_COLOR_RED )
	{
		printf("PgStrg[(%d) %p] ********** \n", color, PgColorName[color] );
		for( PageDesc* Pg = PageStrg[++color]; Pg != NULL; Pg = Pg->next )
		{
			if( Pg->uAddr == NULL )
				continue;

			printf("Pg :Key = 0x%x, addr %p\n", (int)Pg->uKey, Pg->uAddr );
		}
	}
	#undef PG_COLOR_NAME
}