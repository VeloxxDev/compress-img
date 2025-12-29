#ifndef HISTO
#define HISTO


/*
 *  Cells structure for the histogram
 */
typedef struct cell_s cell_t;
struct cell_s {
    unsigned char B;
    int freq;
    struct cell_s *next;
};

/*
 *  Structure of the cell liste
 */
typedef struct liste_s {
    cell_t *tete;
    cell_t *queue;
} liste_t;

/*
 *  Histo structure.
 */
typedef cell_t* histo_t[256][256];

/*
 * Structure of histo_iter_s and his pointeur histo_iter bellow.
 */
typedef struct histo_iter_s {
    int R;
    int G;
    cell_t *current;
} histo_iter_s;

typedef histo_iter_s* histo_iter;


/*
 *  @func This function creates a new cell
 *  @param B is a int wich represents the value for blue in 
 *   the cell
 *  @ret a pointer to the new cell
 */
cell_t* create_cell(int B, cell_t *next);

void insert_cell(cell_t *head, int B);


/*
 * @func deletes a liste
 * @param cell_t is the head of the list to deletes
 * @ret 
 */
void delete_list(cell_t *head);


/*
 * @func creates a 256x256 histogram
 */
histo create_histo();

/*
 * @func Initialisation of the histogram.
 */
void init_histo(histo h, FILE* img);

/*
 * func Suppression of histo.
 */
void delete_histo(histo h);

/*
 *
 */
int give_freq_histo(histo h,int R, int G, int B); 

/*
 *
 */
histo_iter create_histo_iter();









