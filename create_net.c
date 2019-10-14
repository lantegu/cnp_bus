#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>

// #define LINE (0x1<<(atoi(entry->d_name)-1));
#define LINE 0;

typedef struct node {
    int id;
    int *line;
    int edge_num;  //  degree.
    // struct edge *e;
} node;

typedef struct edge {
    node *node_id;
    int weight;
    struct edge *next;
} edge;

struct {
    int sum;
    char **name;
    edge **e;
    node **subway_station;
} subway_net;

void get_more_memory(int *n)
{
    node **tmp1 = (node**)malloc(sizeof(node*)*((*n)+50));
    char **tmp2 = (char**)malloc((*n+50)*sizeof(char*));
    edge **tmp3 = (edge**)malloc((*n+50)*sizeof(edge*));
    memcpy(tmp1,subway_net.subway_station,(*n)*sizeof(node*));
    memcpy(tmp2,subway_net.name,(*n)*sizeof(char*));
    memcpy(tmp3,subway_net.e,(*n)*sizeof(edge*));
    free(subway_net.subway_station);
    free(subway_net.name);
    free(subway_net.e);
    subway_net.subway_station = tmp1;
    subway_net.name = tmp2;
    subway_net.e = tmp3;
    (*n) += 50;
}

int add_a_node(char *buf,int *sum,int *n,struct dirent *entry)
{
    int i;
    //  Get a node.
    for(i=0;i<*sum;i++)
    {
        if(!strcmp(buf,subway_net.name[i]))
            break;
    }
    //  Add a node.
    if(i==*sum)
    {
        if(*sum>=*n)
            get_more_memory(n);
        subway_net.name[*sum] = (char*)malloc(32);
        // subway_net.name[*sum] = (char*)malloc(64);
        subway_net.subway_station[*sum] = (node*)malloc(sizeof(node));
        subway_net.subway_station[*sum]->line = (int*)malloc(sizeof(int)*2);
        subway_net.subway_station[*sum]->line[0] = 1;
        subway_net.subway_station[*sum]->line[1] = atoi(entry->d_name);
        strcpy(subway_net.name[*sum],buf);
        subway_net.subway_station[*sum]->id = *sum;
        subway_net.subway_station[*sum]->edge_num = 0;
        subway_net.e[*sum] = NULL;
        (*sum) ++;
    }
    else 
    {
        int *line_ = subway_net.subway_station[i]->line;
        int num = line_[0];
        int *tmp = (int*)malloc(sizeof(int)*(num+1));
        memcpy(tmp,line_,num*sizeof(int));
        tmp[num] = atoi(entry->d_name);
        tmp[0] ++;
        free(line_);
        subway_net.subway_station[i]->line = tmp;
    }
    return i;
}

void add_an_edge(char *buf,node* from,node* to)
{
    struct edge *tmp = subway_net.e[from->id];
    while(tmp)
    {
        if(tmp->node_id->id!=to->id)
            tmp = tmp->next;
        else 
            break;
    }
    if(tmp==NULL)
    {
        struct edge *p = (struct edge*)malloc(sizeof(struct edge));
        p->node_id = to;
        p->weight = 1;
        p->next = subway_net.e[from->id];
        subway_net.e[from->id] = p;
        from->edge_num ++;
    }
    else 
    {
        tmp->weight ++;
    }
}

void produce_net_from_files()
{
    FILE *fp;
    char buf[32],buf2[16];
    // char buf2[16];
    // int n = 100;
    int n = 1500;
    int sum = 0;
    int i;
    int last;
    subway_net.subway_station = (node**)malloc(sizeof(node*)*n);
    subway_net.name = (char**)malloc(n*sizeof(char*));
    subway_net.e = (edge**)malloc(n*sizeof(edge*));

    DIR *dir = opendir("./bus_data");
    struct dirent *entry;
    while((entry=readdir(dir))!=0)
    {
        if(!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
            continue;
        char path[32] = "./bus_data/";
        strcat(path,entry->d_name);
        fp = fopen(path,"r");
        // char buf[32];
        fgets(buf,32,fp);
        //  Get a node.
        last = add_a_node(buf,&sum,&n,entry);
        //  Get a weight.
        fgets(buf2,16,fp);
        if(!strcmp(buf2,"0"))
            continue ;       
        while(fgets(buf,32,fp))
        {
            //  Get a node.
            i = add_a_node(buf,&sum,&n,entry);
            //  Add edges.
            add_an_edge(buf2,subway_net.subway_station[last],subway_net.subway_station[i]);
            add_an_edge(buf2,subway_net.subway_station[i],subway_net.subway_station[last]);
            //  Get a weight.
            fgets(buf2,16,fp);
            if(!strcmp(buf2,"0"))
                break;
            
            last = i;
        }
        fclose(fp);
    }
    subway_net.sum = sum;
}

int transfor_name_to_id(char *name)
{
    int i;
    for(i=0;i<subway_net.sum;i++)
    {
        if(!strcmp(name,subway_net.name[i]))
            return i;
    }
    printf("Can't find this station in ShenZhen!\n");
    return -1;
}

char *transfor_id_to_name(int id)
{
    if(id < 0 || id >= subway_net.sum)
    {
        printf("Wrong ID!\n");
        return NULL;
    }
    return subway_net.name[id];
}

void free_memory()
{
    int i;
    struct edge *p,*q;
    for(i=0;i<subway_net.sum;i++)
    {
        free(subway_net.name[i]);
        p = subway_net.e[i];
        while(p)
        {
            q = p;
            p = p->next;
            free(q);
        }
        free(subway_net.subway_station[i]->line);
        free(subway_net.subway_station[i]);
    }
    free(subway_net.name);
    free(subway_net.subway_station);
    free(subway_net.e);
}

float average_degree()
{
    // produce_net_from_files();
    int i,degree=0;
    for(i=0;i<subway_net.sum;i++)
    {
        degree += subway_net.subway_station[i]->edge_num;
    }
    return ((float)degree)/subway_net.sum;
}

//  The number of i degree nodes is tmp[i].
int* degree_distribution()
{
    // produce_net_from_files();
    int degree[256];
    memset(degree,0,256*sizeof(int));
    int i;
    for(i=0;i<subway_net.sum;i++)
    {
        degree[subway_net.subway_station[i]->edge_num] ++;
    }
    for(i=0;i<256;i++)
    {
        if(degree[i]!=0)
            degree[0] = i;
    }
    int *tmp = (int*)malloc(sizeof(int)*(degree[0]+1));
    for(i=0;i<=degree[0];i++)
        tmp[i] = degree[i];
    return tmp;
}

float clustering_coefficient(int id)
{
    int n_num = subway_net.subway_station[id]->edge_num;
    if(n_num == 1 || n_num == 0)
        return 0;
    float t = n_num*(n_num - 1)/2.0;
    int *neighbors = (int*)malloc(n_num*sizeof(int));
    int i,j;
    int E = 0;
    struct edge *p = subway_net.e[id];
    for(i=0;i<n_num;i++)
    {
        neighbors[i] = p->node_id->id;
        p = p->next;
    }
    for(i=0;i<n_num;i++)
    {
        p = subway_net.e[neighbors[i]];
        while(p)
        {
            int tmp = p->node_id->id;
            for(j=i;j<n_num;j++)
            {
                if(tmp==neighbors[j])
                {
                    E ++;
                    break;
                }
            }
            p = p->next;
        }
    }
    free(neighbors);
    return E/t;
}

float average_c()
{
    int i=0;
    float sum_c = 0;
    for(i=0;i<subway_net.sum;i++){
        sum_c += clustering_coefficient(i);
        // printf("%d\n",i);
        }
    return sum_c/subway_net.sum;
}

int** transfor_table_to_matrix()
{
    int **matrix = (int**)malloc(sizeof(int*)*subway_net.sum);
    int i;
    for(i=0;i<subway_net.sum;i++)
    {
        matrix[i] = (int*)malloc(subway_net.sum*sizeof(int));
        for(int j=0;j<subway_net.sum;j++)
            matrix[i][j] = 600000;
        matrix[i][i] = 0;
    }
    struct edge *p;
    for(i=0;i<subway_net.sum;i++)
    {
        p = subway_net.e[i];
        while(p)
        {
            matrix[i][p->node_id->id] = 1;
            p = p->next;
        }
    }
    return matrix;
}

float average_shortest_path()
{
    int **matrix = transfor_table_to_matrix();
    int i,j,k;
    int sum = subway_net.sum;
    for(i=0;i<sum;i++)
    {
        for(j=0;j<sum;j++)
        {
            for(k=0;k<sum;k++)
            {
                if(matrix[j][k] > matrix[j][i] + matrix[i][k])
                    matrix[j][k] = matrix[j][i] + matrix[i][k];
            }
        }
        // printf("shortest:%d\n",i);
    }
    int sum_of_path = 0;
    for(i=0;i<sum;i++)
    {
        for(j=0;j<sum;j++)
        {
            if(matrix[i][j]>=600000)
                continue;
            sum_of_path += matrix[i][j];
        }
    }

    ///////////////////////////////////////////
    for(i=0;i<sum;i++)
        free(matrix[i]);
    free(matrix);
    ///////////////////////////////////////////

    return ((float)sum_of_path)/((sum-1)*sum);
}

void delete_all_k_degree_nodes(int k,int *dead,int id)
{
    struct edge *p,*q;
    if(subway_net.subway_station[id]->edge_num <= k)
    {
        subway_net.subway_station[id]->edge_num = -1;
        dead[id] = 1;
        p = subway_net.e[id];
        while(p!=NULL)
        {
            int nid = p->node_id->id;

            if(dead[nid]!=1)
            {
                p->node_id->edge_num --;
                q = subway_net.e[nid];
                struct edge *pre;
                if(q->node_id->id==id)
                {
                    subway_net.e[nid] = q->next;
                }
                else 
                {
                    do{
                        pre = q;
                        q = q->next;
                    } while(q->node_id->id!=id);
                    pre->next = q->next;
                }
                free(q);
                delete_all_k_degree_nodes(k,dead,nid);
                // printf("%d\n",nid);
            }

            q = p;
            p = p->next;
            free(q);
        }
        subway_net.e[id] = NULL;
    }
}

int coreness_of_a_node(int id)
{
    int *dead = (int*)malloc(sizeof(int)*subway_net.sum);
    memset(dead,0,subway_net.sum*sizeof(int));
    int k = 1;
    int i;
    
    while(1)
    {
        for(i=0;i<subway_net.sum;i++)
        {
            if((subway_net.subway_station[i]->edge_num <= k) \
                && (subway_net.subway_station[i]->edge_num != -1))
                break;
        }
        if(i<subway_net.sum)
            delete_all_k_degree_nodes(k,dead,i);
        else 
        {
            if(dead[id])
            {
                free(dead);
                free_memory();
                produce_net_from_files();
                return k;
            }
            else 
                k ++;
        }
    }
}

int coreness_of_a_graph()
{
    int *dead = (int*)malloc(sizeof(int)*subway_net.sum);
    memset(dead,0,sizeof(int)*subway_net.sum);
    int k = 1;
    int i;

    while(1)
    {
        for(i=0;i<subway_net.sum;i++)
        {
            if((subway_net.subway_station[i]->edge_num <= k) && \
                subway_net.subway_station[i]->edge_num != -1)
                break;
        }
        if(i<subway_net.sum)
            delete_all_k_degree_nodes(k,dead,i);
        else 
        {
            i = 0;
            while((i<subway_net.sum)&&(dead[i]))
                i ++;
            if(i==subway_net.sum)
            {
                free(dead);
                free_memory();
                produce_net_from_files();
                    //  Can be deleted but be careful about the free_memory() in main function.
                return k;
            }
            else 
                k ++;
        }
    }
    return 0;
}

int coreness_of_a_station(char *name)
{
    int id = transfor_name_to_id(name);
    if(id==-1)
        return -1;
    return coreness_of_a_node(id);
}

int degree_of_a_station(char *name)
{
    int id = transfor_name_to_id(name);
    if(id==-1)
        return -1;
    return subway_net.subway_station[id]->edge_num;
}

float c_of_a_station(char *name)
{
    int id = transfor_name_to_id(name);
    if(id==-1)
        return -1;
    return clustering_coefficient(id);
}

void c_free(void *pointer)
{
    free(pointer);
}

int get_node_num()
{
    return subway_net.sum;
}

void attack(int id)
{
    edge *p = subway_net.e[id];
    int nid;
    while(p)
    {
        nid = p->node_id->id;
        subway_net.subway_station[nid]->edge_num --;
        edge *q = subway_net.e[nid];
        edge *pre;
        if(q->node_id->id==id)
        {
            subway_net.e[nid] = q->next;
        }
        else 
        {
            do{
                pre = q;
                q = q->next;
            } while(q->node_id->id!=id);
            pre->next = q->next;
        }
        free(q);
        p = p->next;
    }
    p = subway_net.e[id];
    while(p)
    {
        edge *q = p;
        p = p->next;
        free(q);
    }
    free(subway_net.name[id]);
    free(subway_net.subway_station[id]);
    int i;
    for(i=id;i<subway_net.sum-1;i++)
    {
        subway_net.name[i] = subway_net.name[i+1];
        subway_net.subway_station[i] = subway_net.subway_station[i+1];
        subway_net.e[i] = subway_net.e[i+1];
        subway_net.subway_station[i]->id --;
    }
    subway_net.sum --;
}

void random_attack(int percent)
{
    int times = subway_net.sum*percent/100;
    int *done = (int*)malloc(sizeof(int)*times);
    int i = 0,j;
    int id;
    while(i<times)
    {
        srand((unsigned)time(NULL));
        id = rand() % subway_net.sum;
        for(j=0;j<i;j++)
        {
            if(id==done[j])
                break;
        }
        if(j==i)
        {
            done[i] = id;
            i ++;
            attack(id);
        }
    }
    free(done);
}

void intention_attack(int percent)
{
    int times = subway_net.sum*percent/100;
    int *will_do = (int*)malloc(sizeof(int)*times);
    int i=0,j=0,k;
    int *degree = degree_distribution();
    i = degree[0];
    while(j<times)
    {
        j += degree[i];
        k = i;
        i --;
    }
    int need_i = degree[k] - j + times;
    for(j=0,k=0;j<subway_net.sum && k<times;j++)
    {
        if((subway_net.subway_station[j]->edge_num > i) && (subway_net.subway_station[j]->edge_num <= degree[0]))
        {
            if(subway_net.subway_station[j]->edge_num==i+1)
            {
                if(need_i)
                {
                    will_do[k++] = j;
                    need_i --;
                }
                continue;
            }
            will_do[k++] = j;
        }
    }
    // node **tmp = (node**)malloc(sizeof(node*)*k);
    // for(j=0;j<k;j++)
    //     tmp[j] = subway_net.subway_station[will_do[j]];
    for(j=0;j<k;j++)
        attack(will_do[j]-j);   
        // attack(tmp[j]->id);
    free(degree);
    free(will_do);
    // free(tmp);
}

int go_deep_line(int *path,int *line,int which,int id)
{
    node *p = subway_net.subway_station[path[id]];
    int i;
    for(i=1;i<p->line[0];i++)
    {
        if(p->line[i]==which)
        {
            if(go_deep_line(path,line,which,id+1))
            {
                line[id] = which;
                return 1;
            }
            else 
            {
                for(i=1;i<p->line[0];i++)
                {
                    if(p->line[i]==which)
                        continue;
                    if(go_deep_line(path,line,p->line[i],id+1))
                    {
                        line[id] = p->line[i];
                        return 1;
                    }
                }
                return 0;
            }
        }
    }
    return 0;
}

int *change_line(int *path)
{
    int length = path[0];
    int *line_path = (int*)malloc(sizeof(int)*(length+1));
    line_path[0] = length;

    if(go_deep_line(path,line_path,subway_net.subway_station[path[1]]->line[1],1))
        return line_path;
    else 
        return NULL;
}

int deep_search(int start,int *done)
{
    int node_num = 1;
    done[start] = 1;
    edge *p = subway_net.e[start];
    while(p)
    {
        if(!done[p->node_id->id])
            node_num += deep_search(p->node_id->id,done);
        p = p->next;
    }
    return node_num;
}

int num_of_sub_graph()
{
    int num = 0, node_num, max_num = 0;
    int *done = (int*)malloc(sizeof(int)*subway_net.sum);
    memset(done,0,sizeof(int)*subway_net.sum);
    int i;
    while(1)
    {
        for(i=0;i<subway_net.sum;i++)
        {
            if(done[i]==0)
            {
                num ++;
                break;
            }
        }
        if(i==subway_net.sum)
            break;
        node_num = 0;
        node_num += deep_search(i,done);
        if(node_num>max_num)
            max_num = node_num;
    }
    return num;
}

// void main()
// {
//     produce_net_from_files();

//     printf("%d----\n",subway_net.sum);
//     int *degree = degree_distribution();
//     int i;
//     for(i=1;i<=degree[0];i++)
//         printf("%d-----%d\n",i,degree[i]);
//     free(degree);
//     printf("\n");
//     printf("ave_degree:%f\n",average_degree());
//     printf("coefficient:%f\n",average_c());
//     printf("ave_sh_pa:%f\n",average_shortest_path());
//     printf("coreness:%d\n",coreness_of_a_graph());
//     printf("sub:%d\n",num_of_sub_graph());

//     random_attack(1);
//     // intention_attack(1);
    
//     printf("%d----\n",subway_net.sum);
//     degree = degree_distribution();
//     for(i=1;i<=degree[0];i++)
//         printf("%d-----%d\n",i,degree[i]);
//     free(degree);
//     printf("\n");
//     printf("ave_degree:%f\n",average_degree());
//     printf("coefficient:%f\n",average_c());
//     printf("ave_sh_pa:%f\n",average_shortest_path());
//     printf("sub:%d\n",num_of_sub_graph());

//     printf("coreness:%d\n",coreness_of_a_graph());

//     // free_memory();
// }