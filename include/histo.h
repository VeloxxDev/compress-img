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












