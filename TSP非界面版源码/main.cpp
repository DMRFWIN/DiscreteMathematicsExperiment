#include<iostream>

#define MAX 1000
using namespace std;
int g[100][100], x[100], b[100];
int S[100];
int D[100][100];
int cl = 0, k = MAX;
int n;

void GetMinRoadByTx();

void Traveling(int t);

void GetMinRoadByHs();


int main() {


    int num;

    S[0] = 0;
    cout<<"请输入城市个数:"<<endl;
    cin >> n;
    cout<<"请输入路径个数:"<<endl;
    cin >> num;
    cout<<"请按'城市编号 城市编号 权值（距离）'格式输入(起始点是1)：\n"<<endl;
    for (int k = 0; k < num; k++) {
        int a, b, c;
        cin>>a>>b>>c;
        g[a][b] = c;
        g[b][a] = c;
        a--;
        b--;
        D[a][b] = c;
        D[b][a] = c;

    }

    cout<<"贪心法求解结果:"<<endl;
    GetMinRoadByTx();
    cout<<endl;
    cout<<"试探法(回溯法)求解结果："<<endl;
    GetMinRoadByHs();
    /*
    ChooseMethod:
    cout << "请选择要使用的算法：" << endl;
    cout << "1:贪心算法" << endl;
    cout << "2:回溯算法" << endl;
    int method;
    cin >> method;
    switch (method) {
        case 1:
            GetMinRoadByTx();
            break;
        case 2:
            GetMinRoadByHs();
            break;
        default:
            cout << "请输入合法的指令：" << endl;
            goto ChooseMethod;
    }*/


}

void GetMinRoadByHs() {
    int i;
    for (i = 1; i <= n; i++) {
        x[i] = i;
        b[i] = 0;
    }
    Traveling(2);
    cout << "城市路线：" << endl;
    for (i = 1; i <= n; i++)
        cout << b[i] << "-->";
    cout << b[1];
    cout << endl;
    cout << "最短路线长度：" << endl;
    cout << k << endl;
}

void Traveling(int t) {
    int j;
    if (t > n) {
        if (g[x[n]][1] != -1 && (cl + g[x[n]][1] < k)) {
            for (j = 1; j <= n; j++)
                b[j] = x[j];
            k = cl + g[x[n]][1];
        }
    } else {
        for (j = t; j <= n; j++) {
            if (g[x[t - 1]][x[j]] != -1 && (cl + g[x[t - 1]][x[j]] < k)) {
                swap(x[t], x[j]);
                cl += g[x[t - 1]][x[t]];
                Traveling(t + 1);
                cl -= g[x[t - 1]][x[t]];
                swap(x[t], x[j]);
            }
        }
    }
}

void GetMinRoadByTx() {

    /**
     * S[n]用于存储已经访问过的城市
     * D[a][b]用于存储a和b之间的距离
     * flag 访问过为1，没访问过为0
     * i至今已经访问过的城市
     */
    int j, k, l;
    int i;
    i = 1;
    int beng = i;
    int sum = 0;
    int d;
    int flag;
    do {
        k = 1;
        d = 30000;
        do {
            l = 0;
            flag = 0;
            do {
                if (S[l] == k) {//判断该城市是否已被访问过，若被访问过，
                    flag = 1;//则flag为1
                    break;//跳出循环，不参与距离的比较
                } else
                    l++;
            } while (l < i);
            if (flag == 0 && D[k][S[i - 1]] < d) {/*D[k][S[i - 1]]表示当前未被访问的城市k与上一个已访问过的城市i-1之间的距离*/
                j = k;//j用于存储已访问过的城市k
                d = D[k][S[i - 1]];//Dtemp用于暂时存储当前最小路径的值
            }
            k++;
        } while (k < n);
        S[i] = j;//将已访问过的城市j存入到S[i]中
        i++;
        sum += d;//求出各城市之间的最短距离，注意：在结束循环时，该旅行商尚未回到原出发的城市
    } while (i < n);
    sum += D[0][j];//D[0][j]为旅行商所在的最后一个城市与原出发的城市之间的距离
    for (j = 0; j < n; j++) { //输出经过的城市的路径
        cout << S[j] + 1 << "-->";
    }
    cout << beng;
    cout << "\n" << sum;
}