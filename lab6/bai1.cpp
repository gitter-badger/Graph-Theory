typedef struct Edge
{
	int v1;//dinh 1
	int v2;//dinh 2
	double w;//trong so
}Edge;
Edge FindMinEdge(GRAPH g)
{
	//khoi tao gia tri canh ban dau
	Edge EMin;
	EMin.v1=-1;
	//duyet qua cac canh
	for(int i=0;i<g.n;i++)
	for(int j=0;j<g.n;j++)
	{
		//neu co mot dinh duoc chon va dinh con lai chua duoc chon
		if(vertex[i]!=0&&vertex[j]==0&&g.a[i][j]!=0)
		{
			//neu chua co canh nao duoc chon hoac trong so canh nho nhat
			if(EMin.v1==-1||EMin.w>g.a[i][j])
			{
				//thi giu lai va cap nhat canh nho nhat
				//(1)
				EMin.w = g.a[i][j];
				EMin.v1 = i;
				EMin.v2 = j;
			}
		}
	}
	return EMin;
}
void PrimAlgorithm(GRAPH g)
{
	//danh dau mang chua cac dinh chua xet
	for(int i=0;i<g.n;i++)
		vertex[i]=0;
	//neu so canh == so dinh -1
	int nEdge=0;
	//chon canh 0
	vertex[0]=1;
	while(nEdge<g.n-1)
	{	
		Edge Edgemin=FindMinEdge(g);
		//bo vao mang canh
		e[nEdge]=Edgemin;
		//gan nhan dinh dang xet
 		//(2)
 		vertex[Edgemin.v2] = 1;
		g.a[Edgemin.v1][Edgemin.v2] = 0;
		nEdge++;
	}
}