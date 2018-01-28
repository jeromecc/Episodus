/*
GOCR API Copyright (C) 2001 Bruno Barberi Gnecco <brunobg@sourceforge.net>

This program is free software; you can redistribute it and/or
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#ifndef _GOCR_LIST_H

/*
extern "C" {
#endif
*/

/*! \file list.h
  \author Bruno Barberi Gnecco <brunobg@sourceforge.net>
*/

/** @name List
/*@{*/
/**
  \brief Node structure.
*/
struct gocr_node {
	struct gocr_node    *next;		/**< Pointer to next node. */
	struct gocr_node    *previous;	/**< Pointer to prev node. */
	void		        *data;		/**< Pointer to data. */
};
typedef struct gocr_node gocrNode;

/**
*/
struct gocr_list {
	gocrNode    *header;	/**< List header */
	gocrNode 	*tail;		/**< List tail */
	gocrNode 	**fix;		/**< fixes the list_del header problem */
	gocrNode 	**current;	/**< for(each_element) data */
	int 		n;		    /**< number of elements */
	int 		level;		/**< level of nested fors */
};
typedef struct gocr_list gocrList;

/*
 */
void	    gocrlist_init		( gocrList *l );
int	        gocrlist_app		( gocrList *l, void *data );
int	        gocrlist_ins		( gocrList *l, void *data_after, void *data);
int	        gocrlist_ins_order		( gocrList *l, void *data,
					int (*say_when) (const void *, const void *) );
gocrNode*   gocrlist_node_from_data	( gocrList *l, void *data );
int	        gocrlist_del		( gocrList *l, void *data );
void	    gocrlist_free		( gocrList *l );
int	        gocrlist_higher_level	( gocrList *l );
void	    gocrlist_lower_level	( gocrList *l );
void *	    gocrlist_next		( gocrList *l, void *data );
void *	    gocrlist_prev		( gocrList *l, void *data );
void	    gocrlist_sort		( gocrList *l, int (*compare)(const void *, const void *) );

/**
  \retval 0 No.
  \retval 1 Yes.
*/
#define gocrlist_empty(l)			((l)->header == NULL ? 1 : 0)

/**
  \return The header data.
*/
#define gocrlist_get_header(l)		((l)->header->data)

/**
  \return The tail data.
*/
#define gocrlist_get_tail(l)		((l)->tail->data)

/**
  \sa for_each_data.
  \return The current data.
*/
#define gocrlist_get_current(l)		((l)->current[(l)->level]->data)


			NULL : (l)->current[(l)->level]->previous->data )
#define gocrlist_get_cur_next(l)		((l)->current[(l)->level]->next == NULL ? \
			NULL : (l)->current[(l)->level]->next->data )

/**
  \return The number of nodes of the list.
*/
#define gocrlist_total(l)			((l)->n)

#define for_each_data(l)		\
   for ( ; (l)->current[(l)->level]; (l)->current[(l)->level] = \
	(l)->current[(l)->level]->next ) { \
     if ( (l)->fix[(l)->level] ) { /* fix level */\
       int i; \
       for ( i = (l)->level - 1; i >= 0; i-- ) {  \
       /* check if some other copy of (l)->fix[(l)->level] exists */ \
        \
         if ( (l)->fix[i] == (l)->fix[(l)->level] ) break; \
       } \
       if ( i < 0 ) { /* no, it doesn't. Free it */ \
         free((l)->fix[(l)->level]); \
       } \
       (l)->fix[(l)->level] = NULL; \
     }

#define end_for_each(l)			\
 gocrlist_lower_level(l); \
 }

/*
}
#endif
*/


#endif
