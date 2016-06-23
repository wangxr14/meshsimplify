#include"MeshSimplifier.h"
#include<fstream>
#include<iostream>
#include<string>
#include <cstdlib>
#include <algorithm>
using namespace std;

MeshSimplifier::MeshSimplifier()
{
	vertexList.clear();
	faceList.clear();
	edgeList.clear();
	edge_num = 0;
	face_num = 0;
	Vertex a;
	a.setId(0);
	vertexList.push_back(a);//ռס����Ϊ0��λ��
	maxID = 0;

	heap.edgeList = &edgeList;
}

void MeshSimplifier::addVertex(Vertex& p)
{
	maxID++;
	p.setId(maxID);
	vertexList.push_back(p);
}

void MeshSimplifier::addEdge(int u, int v)
{
	Edge e(u,v);
	e.set_order();
	pair<int, int> tmp_e = make_pair(e.u, e.v);
	if (edges.find(tmp_e) == edges.end())//���û��������
	{
		edges[tmp_e] = edge_num;
		edgeList.push_back(e);

		vertexList[e.u].ad_edge[edge_num] = e.v;
		vertexList[e.v].ad_edge[edge_num] = e.u;
		edge_num++;
	}
}

void MeshSimplifier::readin(string filename)
{
	ifstream fin(filename.c_str());
	char flag;
	while (fin >> flag)
	{
		if (flag == '#')
		{
			string s;
			getline(fin, s);
			continue;
		}
		if (flag == 'v' || flag == 'V')
		{
			double tmp[3];
			fin >> tmp[0] >> tmp[1] >> tmp[2];
			Vertex po(tmp[0], tmp[1], tmp[2]);
			addVertex(po);
		}
		if (flag == 'f' || flag == 'F')//face
		{
			int tmp[3];
			fin >> tmp[0] >> tmp[1] >> tmp[2];
			Face tt(tmp[0],tmp[1],tmp[2]);
			tt.cal_normal_vector(vertexList[tmp[0]], vertexList[tmp[1]], vertexList[tmp[2]]);//���㷨����
			faceList.push_back(tt);
			
			Matrix4 kp;
			kp=kp.multi_k(tt.normal_vector);//�������ƽ���K����
			for (int i = 0; i < 3; i++)
			{
				vertexList[tmp[i]].Q = vertexList[tmp[i]].Q + kp;//��K�ӵ����ƽ��Ķ����Q��
				vertexList[tmp[i]].adjacent_face.push_back(faceList.size() - 1);//���������뵽�������������
			}
			addEdge(tmp[0], tmp[1]);
			addEdge(tmp[0], tmp[2]);
			addEdge(tmp[1], tmp[2]);
			
			face_num++;
		}
	}
	fin.close();
	for (int i = 0; i < edgeList.size(); i++)
	{
		cal_edge_cost(i);
		heap.insert(edgeList[i].getCost(), i);
	}
}

void MeshSimplifier::output(string filename)
{
	ofstream fout(filename.c_str());
	vector<int> count;//��¼��i����֮ǰ�ж��ٸ���Ч��
	count.resize(vertexList.size());
	int k = 0;
	for (int i = 1; i < vertexList.size(); i++)
	{
		if (!vertexList[i].existance)
		{
			k++;
			count[i] = k;
			continue;
		}
		else
		{
			count[i] = k;
		}
		fout << "v " << vertexList[i].coord.x << " " << vertexList[i].coord.y << " " << vertexList[i].coord.z << endl;
	}
	for (int i = 0; i < faceList.size(); i++)
	{
		if (faceList[i].existance)
			fout << "f " << faceList[i].v[0] - count[faceList[i].v[0]] << " " << faceList[i].v[1] - count[faceList[i].v[1]] << " " << faceList[i].v[2] - count[faceList[i].v[2]] << endl;
	}

	fout.close();
}

void MeshSimplifier::cal_Q(int x)//�����x��Q
{
	vertexList[x].Q.clear();
	for (int i = 0; i < vertexList[x].adjacent_face.size(); i++)
	{
		if (faceList[vertexList[x].adjacent_face[i]].existance)
		{
			Matrix4 kp;
			kp = kp.multi_k(faceList[vertexList[x].adjacent_face[i]].normal_vector);//�������ƽ���K����
			vertexList[x].Q = vertexList[x].Q + kp;
		}
	}
}

double MeshSimplifier::cal_vQ(Vector4 v, Vector4 t)//�����costֵ
{
	double ret = 0;
	for (int i = 0; i < 4; i++)
	{
		ret += v.value[i] * t.value[i];
	}
	return ret;
}

void MeshSimplifier::cal_edge_cost(int i)
{
	double vx = (vertexList[edgeList[i].u].coord.x + vertexList[edgeList[i].v].coord.x) / 2;
	double vy = (vertexList[edgeList[i].u].coord.y + vertexList[edgeList[i].v].coord.y) / 2;
	double vz = (vertexList[edgeList[i].u].coord.z + vertexList[edgeList[i].v].coord.z) / 2;
	Vector4 v(vx, vy, vz, 1.0);//ѡȡ(v1+v2)/2Ϊv
	Matrix4 Qe = vertexList[edgeList[i].u].Q + vertexList[edgeList[i].v].Q;
	Vector4 t = Qe.left_multi(v);
	double tcost = cal_vQ(v, t);
	edgeList[i].setCost(tcost);
}

void MeshSimplifier::run(double alpha)
{
	int kk = faceList.size();
	cout << kk << endl;
	cout << "faceNum:" << face_num << endl;
	//system("pause");
	double num = kk*alpha;
	cout << "num:" << num << endl;
	
	while (kk>num)
	{
		//cout << "kk:" <<kk<< endl;
		//
		/*for (int i = 0; i < vertexList[944].adjacent_face.size(); i++)
		{
			if (faceList[vertexList[944].adjacent_face[i]].existance)
			cout << vertexList[944].adjacent_face[i] << " ";
		}
		cout << endl;
		{
			
			cout << faceList[1621].v[0] << " "
				<< faceList[1621].v[1] << " "
				<< faceList[1621].v[2] << endl;
		}
		*/
		//
		shrink();
		kk -= 2;
	}
}

void MeshSimplifier::shrink()
{
	int e_remove = heap.nodes[0].position;//��ɾ���ı�
	int v1 = edgeList[e_remove].u;
	int v2 = edgeList[e_remove].v;
	
	//cout << "v1 v2:" << v1 << " " << v2 << endl;
	/*if (v1 == 944 && v2 == 1536)
	{
		cout << "944:" << endl;
		for (int i = 0; i < vertexList[944].adjacent_face.size(); i++)
		{
		if (faceList[vertexList[944].adjacent_face[i]].existance)
		cout << faceList[vertexList[944].adjacent_face[i]].v[0] << " "
		<< faceList[vertexList[944].adjacent_face[i]].v[1] << " "
		<< faceList[vertexList[944].adjacent_face[i]].v[2] << endl;
		}
		cout << "994:" << endl;
		for (int i = 0; i < vertexList[994].adjacent_face.size(); i++)
		{
			if (faceList[vertexList[994].adjacent_face[i]].existance)
				cout << faceList[vertexList[994].adjacent_face[i]].v[0] << " "
				<< faceList[vertexList[994].adjacent_face[i]].v[1] << " "
				<< faceList[vertexList[994].adjacent_face[i]].v[2] << endl;
		}
		system("pause");
	}*/
	edgeList[e_remove].existance = false;//ɾ��
	vertexList[v2].existance = false;//ɾȥһ����
	heap.remove(0);//�������ߴӶ���ɾȥ

	int f_remove1=0,f_remove2=0;//��ɾ����������
	int mk = 0;//���
	//����������ID
	for (int i = 0; i < vertexList[v1].adjacent_face.size(); i++)
	{
		if (faceList[vertexList[v1].adjacent_face[i]].existance)
		{
			if (faceList[vertexList[v1].adjacent_face[i]].has_edge(edgeList[e_remove]))//���������а�����ɾ�ı�
			{
				if (mk == 0)
				{
					f_remove1 = vertexList[v1].adjacent_face[i];
				}
				else f_remove2 = vertexList[v1].adjacent_face[i];
				/*cout << vertexList[v1].adjacent_face[i] << ":"
					<< faceList[vertexList[v1].adjacent_face[i]].v[0] << " "
					<< faceList[vertexList[v1].adjacent_face[i]].v[1] << " "
					<< faceList[vertexList[v1].adjacent_face[i]].v[2] << endl;*/
				mk++;
				faceList[vertexList[v1].adjacent_face[i]].existance = false;//����ɾ��
			}
		}
	}
	//cout << "mk :" << mk << endl;
	//��v2�ڱ���������ֱ��ɾ���ı�ȥ��
	for (map<int, int>::iterator it = vertexList[v2].ad_edge.begin(); it != vertexList[v2].ad_edge.end(); it++)
	{
		if (edgeList[it->first].existance)//�����ߴ���
		{
			//�����������Ҫɾ��������������
			if (faceList[f_remove1].has_edge(edgeList[it->first]) || faceList[f_remove2].has_edge(edgeList[it->first]))
			{
				edgeList[it->first].existance = false;//ɾ����
				heap.remove(edgeList[it->first].position);//�ڶ���ɾ��
			}
		}
	}
	//cout << "delete edge" << endl;
	//�޸�v1������ֵ��ʹ֮��Ϊ�µ�
	double vx = (vertexList[v1].coord.x + vertexList[v2].coord.x) / 2;
	double vy = (vertexList[v1].coord.y + vertexList[v2].coord.y) / 2;
	double vz = (vertexList[v1].coord.z + vertexList[v2].coord.z) / 2;
	vertexList[v1].coord.x = vx;
	vertexList[v1].coord.y = vy;
	vertexList[v1].coord.z = vz;

	//��v2��δɾ�����ڽ�����뵽v1���ڽ�����
	//cout << vertexList[v2].adjacent_face.size() << endl;
	int a = vertexList[v2].adjacent_face.size();
	for (int i = 0; i < a; i++)
	{
		//cout << "i:" << i << endl;
		//cout << vertexList[v2].adjacent_face.size() << endl;
		if (faceList[vertexList[v2].adjacent_face[i]].existance)
		{
			//�޸����ϵĵ�
			for (int j = 0; j < 3; j++)
			{
				if (faceList[vertexList[v2].adjacent_face[i]].v[j] == v2)
				{
					faceList[vertexList[v2].adjacent_face[i]].v[j] = v1;
				}
			}
			//���뵽v1���ڽ���
			vertexList[v1].adjacent_face.push_back(vertexList[v2].adjacent_face[i]);
		}
	}
	//if (a == 166) system("pause");
	//cout << "add Face" << endl;
	//����v1�ڽ���ķ��̣������¼���v1��Q����
	vertexList[v1].Q.clear();
	for (int i = 0; i < vertexList[v1].adjacent_face.size(); i++)
	{
		if (faceList[vertexList[v1].adjacent_face[i]].existance)
		{
			Vertex a, b, c;
			a = vertexList[faceList[vertexList[v1].adjacent_face[i]].v[0]];
			b = vertexList[faceList[vertexList[v1].adjacent_face[i]].v[1]];
			c = vertexList[faceList[vertexList[v1].adjacent_face[i]].v[2]];
			faceList[vertexList[v1].adjacent_face[i]].cal_normal_vector(a,b,c);

			Matrix4 kp;
			kp = kp.multi_k(faceList[vertexList[v1].adjacent_face[i]].normal_vector);//�������ƽ���K����
			vertexList[v1].Q = vertexList[v1].Q + kp;
		}
	}
	//��v2δɾ�����ڽӱ߼��뵽v1���ڽӱ���
	for (map<int, int>::iterator it = vertexList[v2].ad_edge.begin(); it != vertexList[v2].ad_edge.end(); it++)
	{
		if (edgeList[it->first].existance)//�����ߴ���
		{
			//����Ϊv2�ĵ��޸�Ϊv1
			if (edgeList[it->first].u == v2) edgeList[it->first].u = v1;
			else if (edgeList[it->first].v == v2) edgeList[it->first].v = v1;
			//�޸���������ı���Ϣ
			vertexList[v1].ad_edge[it->first] = it->second;
			vertexList[it->second].ad_edge[it->first] = v1;
		}
	}
	//cout << "add edge" << endl;
	//����v1���ڽӱߵ�costֵ
	for (map<int, int>::iterator it = vertexList[v1].ad_edge.begin(); it != vertexList[v1].ad_edge.end(); it++)
	{
		if (edgeList[it->first].existance)//�����ߴ���
		{
			//������һ�������Qֵ
			cal_Q(it->second);
			heap.remove(edgeList[it->first].position);
			cal_edge_cost(it->first);
			heap.insert(edgeList[it->first].getCost(), it->first);
		}
	}
	
	/*if (v1 == 944 && v2 == 1536)
	{
		cout << "944:" << endl;
		for (int i = 0; i < vertexList[944].adjacent_face.size(); i++)
		{
			if (faceList[vertexList[944].adjacent_face[i]].existance)
				cout << faceList[vertexList[944].adjacent_face[i]].v[0] << " "
				<< faceList[vertexList[944].adjacent_face[i]].v[1] << " "
				<< faceList[vertexList[944].adjacent_face[i]].v[2] << endl;
		}
		cout << "994:" << endl;
		for (int i = 0; i < vertexList[994].adjacent_face.size(); i++)
		{
			if (faceList[vertexList[994].adjacent_face[i]].existance)
				cout << faceList[vertexList[994].adjacent_face[i]].v[0] << " "
				<< faceList[vertexList[994].adjacent_face[i]].v[1] << " "
				<< faceList[vertexList[994].adjacent_face[i]].v[2] << endl;
		}
		system("pause");
	}*/
}