#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    if(root==NULL)
    {
        bst_sf *RO = malloc(sizeof(bst_sf));
        if(RO==NULL)
        {
            return NULL;
        }
        RO->mat = mat;
        RO->left_child = NULL;
        RO->right_child = NULL;

        return RO;
    }
    else 
    {
        char ogN = root->mat->name;
        char newN = mat->name;

        if( newN < ogN) // go left
        {
            root->left_child = insert_bst_sf(mat, root->left_child);
        }
        else // go right
        {
            root->right_child = insert_bst_sf(mat, root->right_child);
        }
        
    }
    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    if(root==NULL)
    {
        return NULL;
    }
    if(root->mat->name == name)
    {
        return root->mat;
    }
    if(root->mat->name > name) // go left
    {
        return find_bst_sf(name, root->left_child);
    }
    else
    {
        return find_bst_sf(name, root->right_child);
    }
    return NULL;
}

void free_bst_sf(bst_sf *root) {
    if(root==NULL)
    {
        return;
    }
    else if(root->left_child==NULL && root->right_child==NULL)
    {
        free(root->mat);
        free(root);
    }
    else if(root->left_child==NULL)
    {
        free_bst_sf(root->right_child);
        free(root->mat);
        free(root);
    }
    else if(root->right_child==NULL)
    {
        free_bst_sf(root->left_child);
        free(root->mat);
        free(root);
    }
    else
    {
        free_bst_sf(root->left_child);
        free_bst_sf(root->right_child);
        free(root->mat);
        free(root);
    }
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    
    if(mat1==NULL || mat2 == NULL)
    {
        return NULL;
    }
    
    matrix_sf *m = malloc(sizeof(matrix_sf)+ mat1->num_rows * mat1->num_cols * sizeof(int));
    if(m==NULL)
    {
        return NULL;
    }
    m->name='?';
    m->num_rows = mat1->num_rows;   
    m->num_cols = mat1->num_cols;

    for(int i=0; i<(mat1->num_cols*mat1->num_rows); i++)
    {
        m->values[i] = mat1->values[i] + mat2->values[i];
    }
    
    return m;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if(mat1==NULL || mat2==NULL)
    {
        return NULL;
    }
    matrix_sf *m = malloc(sizeof(matrix_sf) + mat2->num_cols*mat1->num_rows*sizeof(int));
    if(m==NULL)
    {
        return NULL;
    }

    m->name = '?';
    m->num_rows = mat1->num_rows;
    m->num_cols = mat2->num_cols;
    int sum;
    for(int i=0; i<mat1->num_rows; i++)
    {
        for(int j=0; j <mat2->num_cols; j++)
        {
            sum=0;  
            for(int k=0; k<mat1->num_cols;k++)
            {
                int index1 = i * mat1->num_cols + k;
                int index2 = k * mat2->num_cols + j;

                sum+=mat1->values[index1] * mat2->values[index2]; 
            }
            int result_index = i * mat2->num_cols + j;
            m->values[result_index] = sum;
        }
    }
        

   return m;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    if(mat==NULL)
    {
        return NULL;
    }

    matrix_sf *m = malloc(sizeof(matrix_sf) + mat->num_cols*mat->num_rows*sizeof(int));
    if(m==NULL)
    {
        return NULL;
    }

    m->name = '?';
    m->num_cols = mat->num_rows;
    m->num_rows = mat->num_cols;

    int i=0;
    int j= 0;
    int og, tp;
    for(i; i<mat->num_rows;i++)
    {
        for(j=0; j<mat->num_cols; j++)
        {
            og = i * mat->num_cols +j;
            tp = j * mat->num_rows +i;

            m->values[tp]=mat->values[og];
        }
    }

    return m;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    if(expr == NULL)
    {
        return NULL;
    }
    int row;
    int col;
    char *ptr;

    row = (int)strtol(expr, &ptr, 10);
    col = (int)strtol(ptr, &ptr, 10);

    matrix_sf *m = malloc(sizeof(matrix_sf) + row*col*sizeof(int) );
    if(m==NULL)
    {
        return NULL;
    }
    m->name = name;
    m->num_cols=col;
    m->num_rows = row;

    while(*ptr !='[' && *ptr != '\0')
    {
        ptr++;
    }

    if(*ptr == '[')
    {
        ptr++;
    } 

    int index = 0;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            int value = (int)strtol(ptr, &ptr, 10);
            m->values[index++] = value;
        }
        while(*ptr == ' ' || *ptr == ';')
        {
            ptr++;
        } 
    }

    return m;
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
