 #include<bits/stdc++.h>
using namespace std;


string main_path="/home/aakash/Downloads/pg lab 5/";



struct point{

int x_cor;                   /*x coordinate of a point */      
int y_cor;                   /*y coordinate of  a point */
struct cell*pcell;           /* each point has pointer to which cell it belongs */

};

vector<int>xsplits;      /* vector containing where x axis is splitted */
vector<int>ysplits;      /* vector containing where y axis is splitted */

struct cell
{
int start_x;           /*start x coordinate of a cell*/
int start_y;         /*start y coordinate of a cell*/
int end_x;           /*end x coordinate of a cell*/
int end_y;            /*end y coordinate of a cell*/
int count=0;        /*number of points of a cell*/

vector<int>xlist;    /*vector containing x coordinates of all points in that cell*/
vector<int>ylist;     /*vector containing x coordinates of all points in that cell*/

struct bucket*bp;     /*pointer to the bucket of respective cell*/
int exists;           /* tells if the cell still exists or not */
};





struct bucket{                  /* a bucket is data structure containing only the points upto the bucket size required*/

vector<point>bucket_v;  
int exists;                     /*tells if the bucket still exists or not */      
};



int return_xc(int max_point)                    /*function returning maximum x coordinate  in the grid */
{ 

return (rand()%max_point);   

}


int return_yc(int max_point)                          /*function retuurning maximum y coordinate in the grid */
{ 

return (rand()%max_point);   

}


int return_mean(vector<int>&v)              /*function returning mean of coordinates */
{
int size=v.size();
sort(v.begin(),v.end());

if (size % 2 != 0)
      return v[size/2];

else
{
return (v[(size-1)/2] + v[size/2])/2;
}

}




int main()
{
int id,xc,yc;                                                     /* id ,x coordinate,y coordinate */
int points;                                                      /*total number of points */
int max_point;                                                    /* max coordinate of the grid */

int bucket_size;                                                           /*bucket size  */

cout<<"Enter the number of points"<<endl;
cin>>points;

cout<<"Enter maximum coordinate point for x and y axis"<<endl;
cin>>max_point;

cout<<"Enter the buckcet size"<<endl; 
cin>>bucket_size;


FILE*fp;

fp=fopen("/home/aakash/Downloads/pg lab 5/data.txt","w"); 

                                                                  /*data.txt is a file conatining randomly generated synthetic table*/
if(fp==NULL)
{
printf("error in opening file\n");
exit(1);
}


else{

vector<pair<int,int>>main_v;

for(int i=1;i<=points;i++)
{
int x=return_xc(max_point);
int y=return_yc(max_point);
fprintf(fp,"%d\t",i);
fprintf(fp,"%d\t",return_xc(max_point));                                            /*Filling the synthetic table*/

fprintf(fp,"%d\n",return_yc(max_point));  

main_v.push_back(make_pair(x,y));

}

fclose(fp);


map<pair<int,int>, int> umap;

for(int i=0;i<main_v.size();i++)
{
if (umap.find(main_v[i]) == umap.end()) {
            umap[main_v[i]] = 1;
        }
 
        
        else {
            umap[main_v[i]]++;
        }

}

int overflow=0;
for(int i=0;i<main_v.size();i++)
{
int x=main_v[i].first;
int y=main_v[i].second;
if(umap[main_v[i]]>bucket_size)
{
overflow++;
int diff=umap[main_v[i]]-bucket_size;


 string path1=main_path;            
 ostringstream str1; 
 str1 << overflow;
 string name= str1.str();                                           /* Creating files/blocks names as 1.txt,2.txt, and so on*/
 string fipepointer="fp"+name;             
 path1=path1+"overflow"+name+".txt";
 
    char* real_path1;
    string str_obj(path1);
    real_path1 = &str_obj[0];
 FILE*filepointer1;
 filepointer1=fopen(real_path1,"w");


while(diff>0)
{
 
 fprintf(filepointer1,"%d\t",x);
  fprintf(filepointer1,"%d\n",y);
diff--;
}


}

}

vector<cell>total_cell;                                              /*vector containing data about all cells of the grid */

vector<bucket>total_buckets;                                     /*vector containing all buckets */
struct bucket b1;        
b1.exists=1;                                       /*initial bucket taken */
total_buckets.push_back(b1);                                     /*pushing that initial bucket into list of buckets */

total_cell.push_back(cell());                                   /*taking an initial cell*/

total_cell[0].start_x=0;                                      /*initial starting coordinates of the initial cell*/
total_cell[0].end_x=max_point;
total_cell[0].start_y=0;
total_cell[0].end_y=max_point;
total_cell[0].exists=1;

total_cell[0].bp=&b1;

FILE*fp=fopen("/home/aakash/Downloads/pg lab 5/data.txt","r"); 

int point_count=0;



/*code for Insertion and Splitting begins from here----------------------------------------------------------------------------*/



while(!feof(fp)&&point_count!=points){

int id,x,y;
 fscanf(fp, "%d\t%d\t%d", &id, &x, &y);


 /*cout<<id<<"\t"<<x<<"\t"<<y<<endl;*/
 
point_count++;
 
 for(int i=0;i<total_cell.size();i++)
 {
 
 /* below statement checks whether the point read lies in the cell and if the cell also exists or not*/
 
 if(x>=total_cell[i].start_x&&x<=total_cell[i].end_x&&y>=total_cell[i].start_y&&y<=total_cell[i].end_y&&total_cell[i].exists==1) 
 {
 
/*Now checking whether the current cell's size is less than bucket size ,then no issue insert point in the grid */

 if(total_cell[i].count<bucket_size){ 
 
 total_cell[i].bp->bucket_v.push_back({x,y,&total_cell[i]});
 total_cell[i].count++;
 total_cell[i].xlist.push_back(x);
 /*cout<<"now my size is"<<total_cell[i].count<<endl;*/
  total_cell[i].ylist.push_back(y);
 }
 
 else                                                              /*if the bucket of the cell was already full*/
 {
  total_cell[i].bp->bucket_v.push_back({x,y,&total_cell[i]});

 total_cell[i].xlist.push_back(x);
 /*cout<<"now my size is"<<total_cell[i].count<<endl;*/
  total_cell[i].ylist.push_back(y);
  
  
 struct bucket b2;                                                    /*create a new bucket and add that bucket into list of buckets */
total_buckets.push_back(b2);   

total_cell[i].bp->bucket_v.clear();
                         
int x_mean=return_mean(total_cell[i].xlist);                             /*finding mean on x axis*/
 int y_mean=return_mean(total_cell[i].ylist);                              /*findig mean on y axis*/
 
 /*cout<<"I am gonna split now"<<endl; */
 
 int point_xleft=0,point_xright=0;                                      /*number of points which goes to left and right of mean point*/
 
 for(int s=0;s<total_cell[i].xlist.size();s++)                          /*counting how many points would go to left of mean point */
 {
 if(total_cell[i].xlist[s]<x_mean)
 {
 point_xleft++;
 
 }
 else
 {
 point_xright++;                                                            /*counting how many points would go to right of mean point */
 }
 
}
 
int point_yup=0,point_ydown=0;                                      /*number of points which goes to up  and down of mean point*/
 for(int s=0;s<total_cell[i].ylist.size();s++)                          /*counting how many points would go to down of mean point */
 {
 if(total_cell[i].ylist[s]<y_mean)
 {
 point_ydown++;
 
 }
 else
 {
 
 point_yup++;                                                            /*counting how many points would go to upward of mean point */
 }
 
}
 
 
 

 
 if(point_xleft<=bucket_size&&point_xright<=bucket_size)                       //then divide perpendicular to x-axis//
 {
 xsplits.push_back(x_mean);
 
  struct cell c1;
 c1.start_x=total_cell[i].start_x;                     /*Dividing the original full cell along the mean and creating a new cell*/
 
c1.start_y=total_cell[i].start_y;
c1.end_x=x_mean;
c1.end_y=total_cell[i].end_y;                     /*Assignment of coordinates to the new cells*/

c1.bp=total_cell[i].bp;
c1.exists=1;
 
 
 
 c1.xlist.clear();
c1.ylist.clear();
 
 for(int q=0;q<point_xleft;q++)         /*Inserting X and Y coordinates of points to their respective created grid cell after splitting*/
 {

 c1.xlist.push_back(total_cell[i].xlist[q]);
 c1.ylist.push_back(total_cell[i].ylist[q]);
  /*cout<<total_cell[i].xlist[q]<<"\t"<<total_cell[i].ylist[q]<<endl;*/
 
 }
 
 /*cout<<c1.xlist.size()<<"size of left one"<<endl;*/
 
 
 
 
 /*cout<<"Coordinates of newly created cell are"<<endl;*/
 /*cout<<c1.start_x<<endl;
 cout<<c1.end_x<<endl;
 cout<<c1.start_y<<endl;
 cout<<c1.end_y<<endl;*/
 
 
 
 struct cell c2;
 c2.start_x=x_mean;
c2.start_y=total_cell[i].start_y;
c2.end_x=total_cell[i].end_x;
c2.end_y=total_cell[i].end_y;

c2.bp=&b2;
c2.exists=1;



/*cout<<"kon inside ja rha hai"<<endl;*/


c2.xlist.clear();
c2.ylist.clear();

 for(int r=0;r<point_xright-1;r++)
 {

 c2.xlist.push_back(total_cell[i].xlist[point_xleft+r]);
 c2.ylist.push_back(total_cell[i].ylist[point_xleft+r]);

 
 /*cout<<total_cell[i].xlist[point_xleft+r]<<"\t"<<total_cell[i].ylist[point_xleft+r]<<endl;*/
 }
 
 
 /*cout<<c2.xlist.size()<<"size of right one"<<endl;*/



total_cell.push_back(c1);
total_cell.push_back(c2);
 
  /*cout<<"Coordinates of newly created cell are"<<endl;*/
 /*cout<<c2.start_x<<endl;
 cout<<c2.end_x<<endl;
 cout<<c2.start_y<<endl;
 cout<<c2.end_y<<endl;*/
 
 }
 else{                               /*If division perpendicular to x-axis is failed then divide perpendicular to y-axis*/
 
 ysplits.push_back(y_mean);
 
  struct cell c1;
 c1.start_x=total_cell[i].start_x;
 
c1.start_y=total_cell[i].start_y;
c1.end_x=total_cell[i].end_x;
c1.end_y=y_mean;

c1.bp=total_cell[i].bp;
c1.exists=1;
 
 /*cout<<"kon inside ja rha hai"<<endl;*/
 
 
c1.xlist.clear();
c1.ylist.clear();

 
 for(int q=0;q<point_ydown;q++)
 {

 c1.xlist.push_back(total_cell[i].xlist[q]);
 c1.ylist.push_back(total_cell[i].ylist[q]);
  /*cout<<total_cell[i].xlist[q]<<"\t"<<total_cell[i].ylist[q]<<endl;*/
 
 }
 
 /*cout<<c1.xlist.size()<<"size of down one"<<endl;*/
 
 /*cout<<"Coordinates of newly created cell are"<<endl;*/
 /*cout<<c1.start_x<<endl;
 cout<<c1.end_x<<endl;
 cout<<c1.start_y<<endl;
 cout<<c1.end_y<<endl;*/
 
 struct cell c2;
 
 c2.start_x=total_cell[i].start_x;
c2.start_y=y_mean;
c2.end_x=total_cell[i].end_x;
c2.end_y=total_cell[i].end_y;

c2.bp=&b2;
c2.exists=1;


c2.xlist.clear();
c2.ylist.clear();

/*cout<<"kon inside ja rha hai"<<endl;*/

 for(int r=0;r<point_yup-1;r++)
 {

 c2.xlist.push_back(total_cell[i].xlist[point_ydown+r]);
 c2.ylist.push_back(total_cell[i].ylist[point_ydown+r]);

 
/* cout<<total_cell[i].xlist[point_xleft+r]<<"\t"<<total_cell[i].ylist[point_xleft+r]<<endl;*/
 }
 
 
 /*cout<<c2.xlist.size()<<"size of up one"<<endl;*/



total_cell.push_back(c1);
total_cell.push_back(c2);
 
 /* cout<<"Coordinates of newly created cell are"<<endl;*/
 /*cout<<c2.start_x<<endl;
 cout<<c2.end_x<<endl;
 cout<<c2.start_y<<endl;
 cout<<c2.end_y<<endl;*/
 }
 total_cell[i].exists=0;                                                  /*make the overloded cell non existent */
 total_cell[i].bp->exists=0;                                           /*make the overloaded cell bucket non existent*/
 }

 }
 }

}

/*cout<<"total_cell size is"<<total_cell.size()<<endl;*/





/*Code for splitting and insertion ends here---------------------------------------------------------------------*/


/*Printing and Writing to file the contents of each bucket----------------------------------------------------------------------- */




int counter_of_cells=1;
int counter_of_buckets=1;
for(int m=0;m<total_cell.size();m++)
 {
 if(total_cell[m].exists==1){
 
 
  string path1=main_path;            
 ostringstream str1; 
 str1 << counter_of_buckets;
 string name= str1.str();                                          /* Creating files/blocks for bucket named as bucket1.txt,bucket2.txt, and so on*/
 string fipepointer="fp"+name;             
 path1=path1+"bucket"+name+".txt";
 
    char* real_path1;
    string str_obj(path1);
    real_path1 = &str_obj[0];
 FILE*filepointer;
 filepointer=fopen(real_path1,"w");
 
 
/*cout<<"Now cell no=="<<(counter_of_cells)<<endl;*/
counter_of_cells++;

int size_counter=1;
 for(int n=0;n<total_cell[m].xlist.size();n++)
 {
 if(size_counter<=bucket_size){
 
 /*cout<<total_cell[m].xlist[n]<<"\t"<<total_cell[m].ylist[n]<<endl;*/
 fprintf(filepointer,"%d\t",total_cell[m].xlist[n]);
  fprintf(filepointer,"%d\n",total_cell[m].ylist[n]);
 size_counter++;
 
 }
 else
 {
 fclose(filepointer);
 /*cout<<"break needed"<<endl;*/
 counter_of_buckets++;
string path1=main_path;            
 ostringstream str1; 
 str1 << counter_of_buckets;
 string name= str1.str();                               /* Creating files/blocks for bucket named as bucket1.txt,bucket2.txt, and so on*/
 string fipepointer="fp"+name;             
 path1=path1+"bucket"+name+".txt";
 
    char* real_path1;
    string str_obj(path1);
    real_path1 = &str_obj[0];
 FILE*filepointer;
 filepointer=fopen(real_path1,"w");
 
  /*cout<<total_cell[m].xlist[n]<<"\t"<<total_cell[m].ylist[n]<<endl;*/
fprintf(filepointer,"%d\t",total_cell[m].xlist[n]);
  fprintf(filepointer,"%d\n",total_cell[m].ylist[n]);
 
 
 size_counter=1;
 }
 }
 fclose(filepointer);
 counter_of_buckets++;
 /*cout<<"x,y over"<<endl;*/
 

 
 }
 
}
/*Printing and Writing to file the contents of each bucket ends here------------------------------------------------------------- */



/*Code for printing contents of grid cells is given below*/

/*for(int i=0;i<total_cell.size();i++)                
 {

if(total_cell[i].exists==1)
{

 cout<<"Coordinates of cell no."<<(i+1)<<"created in the grid  are"<<endl;
 cout<<"startx"<<total_cell[i].start_x<<endl;
 cout<<"endx"<<total_cell[i].end_x<<endl;
 cout<<"starty"<<total_cell[i].start_y<<endl;
 cout<<"endy"<<total_cell[i].end_y<<endl;



cout<<"The coordinates of the point in the grid are"<<endl;

 for(int n=0;n<total_cell[i].xlist.size();n++)
 {
 
 
 cout<<total_cell[i].xlist[n]<<"\t"<<total_cell[i].ylist[n]<<endl;

}

}
}*/


}


cout<<"Buckets Created Successfully"<<endl;
return 0;
}

