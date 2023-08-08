#include <bits/stdc++.h>
#define endl "\n"
#define ll long long
#define vll vector<ll>
#define pb push_back
#define mod 1000000007
#define MAX 1e9
#define MIN -1e9
#define flash ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;
void average_turnaround_time(ll turnaround[], ll n)
{
    double res = 0;
    for (int i = 0; i < n; i++)
    {
        res += turnaround[i];
    }
    res /= n;
    cout << "Average turnaround time is " << res << endl;
}
void average_waiting_time(ll waiting[], ll n)
{
    double res = 0;
    for (int i = 0; i < n; i++)
    {
        res += waiting[i];
    }
    res /= n;
    cout << "Average waiting time is " << res << endl;
}
void average_response_time(ll response[], ll n)
{
    double res = 0;
    for (int i = 0; i < n; i++)
    {
        res += response[i];
    }
    res /= n;
    cout << "Average response time is " << res << endl;
}
void overall_throughput(ll timer, ll n)
{
    double res = timer / n;
    cout << "Overall throughput is " << res << endl;
}
int main()
{
    // flash;
    int number;
    vector<ll> arrival_time;
    vector<ll> cpu_burst;
    ll n = 0;
    cout<<"Enter the Number of Process:";
    cin>>n;
    cout<<"Enter Arrival Time and CPU Burst For All Process:"<<endl;
    for(int i=0;i<n;i++){
        ll at,cp;
        cin>>at>>cp;
        arrival_time.push_back(at);
        cpu_burst.push_back(cp);
    }
    bool ok = 1;
    while (ok)
    {
        cout << "Choose the scheduling algo on which you have to run the given processes"
             << endl;
        cout << "1) First come first serve (FCSF)" << endl;
        cout << "2) Shortest job first (SJF)" << endl;
        cout << "3) Shortest time remainig first (SRTF)" << endl;
        cout << "4) Round Robin (RR)" << endl;
        cout << "5) Exit" << endl;
        cout << "Enter your choice ";
        ll choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            ll turnaround[n];
            ll waiting[n];
            ll response[n];
            queue<pair<ll, ll>> q;
            for (int i = 0; i < n; i++)
            {
                response[i] = MAX;
            }
            ll timer = 0;
            ll next = 0;
            while (1)
            {
                if (q.empty())
                {
                    if (next < n)
                    {
                        while (timer < arrival_time[next])
                        {
                            cout << "cpu is idle ";
                            timer++;
                        }
                        q.push({cpu_burst[next], next + 1});
                        next++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (next < n && timer == arrival_time[next])
                    {
                        q.push({cpu_burst[next], next + 1});
                        next++;
                    }
                    pair<ll, ll> p = q.front();
                    q.pop();
                    for (int i = 0; i < cpu_burst[p.second - 1]; i++)
                    {
                        cout << p.second << " ";
                        timer++;
                        if (next < n && timer == arrival_time[next])
                        {
                            q.push({cpu_burst[next], next + 1});
                            next++;
                        }
                    }
                    // timer += cpu_burst[p.second - 1];
                    turnaround[p.second - 1] = timer - arrival_time[p.second - 1];
                    waiting[p.second - 1] = turnaround[p.second - 1] - cpu_burst[p.second - 1];
                    response[p.second - 1] = min(response[p.second - 1], timer);
                }
            }
            cout << endl;
            average_turnaround_time(turnaround, n);
            average_waiting_time(waiting, n);
            average_response_time(response, n);
            overall_throughput(timer, n);
            break;
        }
        case 2:
        {
            priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
                pq;
            ll turnaround[n];
            ll waiting[n];
            ll response[n];
            for (int i = 0; i < n; i++)
            {
                response[i] = MAX;
            }
            ll timer = 0;
            ll next = 0;
            while (1)
            {
                if (pq.empty())
                {
                    if (next < n)
                    {
                        while (timer < arrival_time[next])
                        {
                            cout << "cpu is idle ";
                            timer++;
                        }
                        pq.push({cpu_burst[next], next + 1});
                        next++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (next < n && timer == arrival_time[next])
                    {
                        pq.push({cpu_burst[next], next + 1});
                        next++;
                    }
                    pair<ll, ll> p = pq.top();
                    pq.pop();
                    for (int i = 0; i < cpu_burst[p.second - 1]; i++)
                    {
                        cout << p.second << " ";
                        timer++;
                        if (next < n && timer == arrival_time[next])
                        {
                            pq.push({cpu_burst[next], next + 1});
                            next++;
                        }
                    }
                    // timer += cpu_burst[p.second - 1];
                    turnaround[p.second - 1] = timer - arrival_time[p.second - 1];
                    waiting[p.second - 1] = turnaround[p.second - 1] - cpu_burst[p.second - 1];
                    response[p.second - 1] = min(response[p.second - 1], timer);
                }
            }
            cout << endl;
            average_turnaround_time(turnaround, n);
            average_waiting_time(waiting, n);
            average_response_time(response, n);
            overall_throughput(timer, n);
            break;
        }
        case 3:
        {
            ll store_cpuburst[n];
            ll cpu_burst1[n];
            priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
                pq;
            ll turnaround[n];
            ll waiting[n];
            ll response[n];
            for (int i = 0; i < n; i++)
            {
                cpu_burst1[i] = cpu_burst[i];
                store_cpuburst[i] = cpu_burst1[i];
                response[i] = MAX;
            }
            ll timer = 0;
            ll next = 0;
            while (1)
            {
                if (pq.empty())
                {
                    if (next < n)
                    {
                        while (timer < arrival_time[next])
                        {
                            cout << "cpu is idle ";
                            timer++;
                        }
                        pq.push({cpu_burst1[next], next + 1});
                        next++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (next < n && timer == arrival_time[next])
                    {
                        pq.push({cpu_burst1[next], next + 1});
                        next++;
                    }
                    pair<ll, ll> p = pq.top();
                    pq.pop();
                    ll mx = cpu_burst1[p.second - 1];
                    for (int i = 0; i < mx; i++)
                    {
                        cout << p.second << " ";
                        timer++;
                        cpu_burst1[p.second - 1]--;
                        if (next < n && timer == arrival_time[next])
                        {
                            pq.push({cpu_burst1[next], next + 1});
                            next++;
                            if (pq.top().first < cpu_burst1[p.second - 1])
                            {
                                // cout << timer << endl;
                                pq.push({cpu_burst1[p.second - 1], p.second});
                                break;
                            }
                        }
                    }
                    if (cpu_burst1[p.second - 1] == 0)
                    {
                        turnaround[p.second - 1] = timer - arrival_time[p.second - 1];
                        waiting[p.second - 1] = turnaround[p.second - 1] -
                                                store_cpuburst[p.second - 1];
                    }
                    response[p.second - 1] = min(response[p.second - 1], timer);
                }
            }
            cout << endl;
            average_turnaround_time(turnaround, n);
            average_waiting_time(waiting, n);
            average_response_time(response, n);
            overall_throughput(timer, n);
            break;
        }
        case 4:
        {
            cout << "Enter the time Quanta for the RR : ";
            ll time_quanta;
            ll store_cpuburst[n];
            ll response[n];
            cin >> time_quanta;
            ll cpu_burst1[n];
            queue<pair<ll, ll>> q;
            for (int i = 0; i < n; i++)
            {
                cpu_burst1[i] = cpu_burst[i];
                store_cpuburst[i] = cpu_burst1[i];
                response[i] = MAX;
            }
            ll turnaround[n];
            ll waiting[n];
            ll timer = 0;
            ll next = 0;
            while (1)
            {
                if (q.empty())
                {
                    if (next < n)
                    {
                        while (timer < arrival_time[next])
                        {
                            cout << "Cpu is idle ";
                            timer++;
                        }
                        q.push({cpu_burst1[next], next + 1});
                        next++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (next < n && timer == arrival_time[next])
                    {
                        q.push({cpu_burst1[next], next + 1});
                        next++;
                    }
                    pair<ll, ll> p = q.front();
                    q.pop();
                    ll mx = cpu_burst1[p.second - 1];
                    for (int i = 0; i < min(mx, time_quanta); i++)
                    {
                        cout << p.second << " ";
                        timer++;
                        cpu_burst1[p.second - 1]--;
                        if (next < n && timer == arrival_time[next])
                        {
                            q.push({cpu_burst1[next], next + 1});
                            next++;
                        }
                    }
                    if (cpu_burst1[p.second - 1] == 0)
                    {
                        turnaround[p.second - 1] = timer - arrival_time[p.second - 1];
                        waiting[p.second - 1] = turnaround[p.second - 1] -
                                                store_cpuburst[p.second - 1];
                    }
                    else
                    {
                        q.push({cpu_burst1[p.second - 1], p.second});
                    }
                    if (!q.empty())
                    {
                        cout << "Overhead ";
                        timer++;
                    }
                    response[p.second - 1] = min(response[p.second - 1], timer);
                }
            }
            cout << endl;
            average_turnaround_time(turnaround, n);
            average_waiting_time(waiting, n);
            average_response_time(response, n);
            overall_throughput(timer, n);
            break;
        }
        case 5:
        {
            ok = 0;
            break;
        }
        }
    }
    return 0;
}