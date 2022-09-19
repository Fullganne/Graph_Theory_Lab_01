#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;

struct GRAPH
{
    int sodinh;
    int a[MAX][MAX];
};

void readGRAPH(string fn, GRAPH& g)
{
    ifstream f;
    f.open(fn + ".txt");
    if (f.is_open())
    {
        f >> g.sodinh;
        for (int i = 0; i < g.sodinh; i++)
            for (int j = 0; j < g.sodinh; j++) f >> g.a[i][j];
        f.close();
    }
    else
        cout << "Khong mo duoc file!!!" << endl;
}

void printGRAPH(GRAPH g)
{
    cout << "So dinh cua do thi: " << g.sodinh << endl;
    for (int i = 0; i < g.sodinh; i++)
    {
        for (int j = 0; j < g.sodinh; j++) cout << setw(4) << g.a[i][j];
        cout << endl;
    }
}

int KiemTraMaTranKeHopLe(GRAPH& g)
{
    for (int i = 0; i < g.sodinh; i++)
        if (g.a[i][i] != 0) return 0;
    return 1;
}

int KiemTraDoThiVoHuong(GRAPH& g)
{
    for (int i = 0; i < g.sodinh; i++)
    {
        for (int j = i + 1; j < g.sodinh; j++)
        {
            if (g.a[i][j] != g.a[j][i])
                return 0;
        }
    }
    return 1;
}

int getSoCanh(GRAPH& g)
{
    int socanh = 0;
    for (int i = 0; i < g.sodinh; i++)
    {
        for (int j = 0; j < g.sodinh; j++)
        {
            if (j >= i)
            {
                if (!KiemTraDoThiVoHuong(g))
                {
                    socanh += g.a[i][j];
                    socanh += g.a[j][i];
                }
                else
                    socanh += g.a[i][j];
            }
        }
    }
    return socanh;
}

void getBacDinhDT(GRAPH g)
{
    int Bac;
    for (int i = 0; i < g.sodinh; i++)
    {
        Bac = 0;
        for (int j = 0; j < g.sodinh; j++)
            if (g.a[i][j] > 0)
                Bac++;
        cout << "Bac dinh " << i + 1 << ": " << Bac << endl;
    }
}

void getBacLonNhat(GRAPH& g, int arr[])
{
    int max = 0, Bac;
    for (int i = 0; i < g.sodinh; i++)
    {
        Bac = 0;
        for (int j = 0; j < g.sodinh; j++)
            if (g.a[i][j] > 0)         //Tính bậc của từng đỉnh
                Bac++;
        arr[i] = Bac;
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    cout << "Dinh co bac lon nhat: ";
    for (int i = 0; i < g.sodinh; i++)
        if (arr[i] == max)
            cout << i + 1 << " ";
    cout << endl;
}

void getBacNhoNhat(GRAPH& g, int arr[])
{
    int min = MAX;
    cout << "Dinh co bac nho nhat: ";
    for (int i = 0; i < g.sodinh; i++)
        if (arr[i] < min)
            min = arr[i];
    for (int i = 0; i < g.sodinh; i++)
        if (arr[i] == min)
            cout << i + 1 << " ";
    cout << endl;
}

void getBacChanBacLe(GRAPH& g, int arr[])
{
    cout << "Cac dinh bac chan: ";
    for (int i = 0; i < g.sodinh; i++)
    {
        if (arr[i] % 2 == 0)
            cout << i + 1 << " ";
    }
    cout << endl;
    cout << "Cac dinh bac le: ";
    for (int i = 0; i < g.sodinh; i++)
    {
        if (arr[i] % 2 != 0)
            cout << i + 1 << " ";
    }
    cout << endl;
}

void DinhCoLapDinhTreo(GRAPH g, int arr[])
{
    int demcl = 0, demtr = 0;
    for (int i = 0; i < g.sodinh; i++)
    {
        if (arr[i] == 0)
            demcl++;
        if (arr[i] == 1)
            demtr++;
    }
    if (demcl == 0)
        cout << "Khong co dinh co lap!" << endl;
    else
    {
        cout << "Cac dinh co lap: ";
        for (int i = 0; i < g.sodinh; i++)
            if (arr[i] == 0) cout << i + 1 << " ";
        cout << endl;
    }
    if (demtr == 0)
        cout << "Khong co dinh treo!" << endl;
    else
    {
        cout << "Cac dinh treo: ";
        for (int i = 0; i < g.sodinh; i++)
            if (arr[i] == 1) cout << i + 1 << " ";
        cout << endl;
    }
}

int main()
{
    GRAPH g;
    int bac_moi_dinh[MAX];
    string fn;
    cout << "Nhap ten file: ";
    cin >> fn;
    readGRAPH(fn, g);
    printGRAPH(g);
    if (!KiemTraMaTranKeHopLe(g))
        cout << "Ma tran ke khong hop le!" << endl;
    else
        cout << "Ma tran ke hop le!" << endl;
    if (!KiemTraDoThiVoHuong(g))
        cout << "Day la do thi co huong!" << endl;
    else
        cout << "Day la do thi vo huong!" << endl;
    cout << "So canh cua do thi: " << getSoCanh(g) << endl;
    getBacDinhDT(g);
    getBacLonNhat(g, bac_moi_dinh);
    getBacNhoNhat(g, bac_moi_dinh);
    getBacChanBacLe(g, bac_moi_dinh);
    DinhCoLapDinhTreo(g, bac_moi_dinh);
    return 0;
}
