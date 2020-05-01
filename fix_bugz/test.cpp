#include <stdio.h>
#include <string.h>


enum PAGE_COLOR
{
	PG_COLOR_GREEN = 1, /* page may be released without high overhead */
	PG_COLOR_YELLOW, /* nice to have */
	PG_COLOR_RED	/* page is actively used */
};

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


/* Prepare from 2 chars the key of the same configuration as in PageKey */
#define CALC_PAGE_KEY( Addr, Color )	(  ((Color) + (*Addr)) << 8 ) 


/**
 * Descriptor of a single guest physical page
 */
struct PageDesc
{
	PageKey			uKey;	
	PageKey*        uAddr;
 
	PageDesc		*next, *prev;
};

#define PAGE_INIT( Desc, Addr, Color )              \
    {                                               \
        (Desc).uKey = (PageKey)CALC_PAGE_KEY( Addr, Color ); \
        (Desc).next = (Desc).prev = NULL;           \
    }
        

/* storage for pages of all colors */
static PageDesc* PageStrg[ 3 ];


void PageStrgInit()
{
	memset( PageStrg, 0, sizeof(&PageStrg) );
}

PageDesc* PageFind( void* ptr, int color )
{
	for( PageDesc* Pg = PageStrg[color]; Pg; Pg = Pg->next )
        if( (int)(Pg->uKey) == CALC_PAGE_KEY((char*)ptr, color) )
           return Pg;                                                                                                                                     
    return NULL;
}

PageDesc* PageReclaim( int cnt )
{
	int color = 0;
	PageDesc* Pg;
	while( cnt )
	{
		Pg = Pg->next;
		// PageRemove( PageStrg[ color ] );
		cnt--;
		if( Pg == NULL )
		{
			color++;
			Pg = PageStrg[ color ];
		}
	}
	return Pg;
}
            
PageDesc* PageInit( void* ptr, int color )
{
    PageDesc* pg = new PageDesc;
    if( pg )
    {
    	PAGE_INIT(*pg, (char*)ptr, color);
    }
    else{
        printf("Allocation has failed\n");
    }
    return pg;
}

/**
 * Print all mapped pages
 */
void PageDump()
{
	int color = 0;
	#define PG_COLOR_NAME(clr) #clr
	const char* PgColorName[] = 
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

int main()
{
	return 0;
}