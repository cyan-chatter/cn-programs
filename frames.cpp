#include <bits/stdc++.h>

using namespace std;

binary_semaphore semaphore(0);

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define sz(v) (int)(v).size()

using vi = vector<int>;

struct StopAndWait {
    int totalFrames, roundTripTime;

    string acknowledgement(int i) {
        int delay = rng() % (3 * roundTripTime);
        if (delay > roundTripTime) return "";
        const auto start_time = chrono::high_resolution_clock::now();
        while (1) {
            auto end_time = chrono::high_resolution_clock::now();
            auto diff = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
            if (diff.count() < delay) continue;
//        cerr << "Time Taken : " << diff.count() << " ms\n";
            return "Frame " + to_string(i) + " received";
//        semaphore.release();
        }
    }

    void sendFrame(int i) {
        while (1) {
            cout << "Frame " << i << " sent\n";
//        semaphore.try_acquire_for(chrono::duration<int>(roundTripTime));
            string s = acknowledgement(i);
            if (s.empty()) continue;
            cout << s << '\n';
            break;
        }
    }

    void simulate() {
        cout << "Enter total number of frames to be sent: \n";
        cin >> totalFrames;
        cout << "Enter round trip time: \n";
        cin >> roundTripTime;

        for (int x = 0; x < totalFrames; x++) sendFrame(x);
    }
} sw;

struct GoBackN {
    int totalFrames, timeoutInterval, windowSize;

    int acknowledgement(int i, int sz) {
        for(int x=0;x<sz;x++) {
            int interval = rng() % (timeoutInterval + 5);
            if(interval > timeoutInterval) return i + x;
            cout<<"Frame "<<i+x<<" received\n";
        }
        return -1;
    }

    void sender() {
        for(int i=0, j=0;i<totalFrames;){
            int sz = 0;
            while(j < totalFrames and j<i+windowSize) cout<<"Frame "<<j<<" sent\n", ++j, ++sz;
            int k = acknowledgement(i, sz);
            i = (k == -1) ? j : k, j = i;
        }
    }

    void simulate() {
        cout<<"Enter total number of frames to be sent: \n";
        cin>>totalFrames;
        cout<<"Enter window size: \n";
        cin>>windowSize;
        cout<<"Enter timeout interval: \n";
        cin>>timeoutInterval;

        sender();
    }
} gbn;

struct SelectiveRepeat {
    int totalFrames, timeoutInterval, windowSize;

    vi acknowledgement(vi v) {
        vi rem;
        for(auto &x: v) {
            int interval = rng() % (timeoutInterval + 5);
            if(interval > timeoutInterval) {
                rem.push_back(x);
                continue;
            }
            cout<<"Frame "<<x<<" received\n";
        }
        return rem;
    }

    void sender() {
        for(int i=0, j=0;i<totalFrames;){
            vi v;
            while(j < totalFrames and j<i+windowSize) cout<<"Frame "<<j<<" sent\n", v.push_back(j), ++j;
            vi rem = acknowledgement(v);
            reverse(rem.begin(), rem.end());
            for(auto &x: rem) {
                cout<<"Frame "<<x<<" sent\n";
                while(!acknowledgement({x}).empty()) cout<<"Frame "<<x<<" sent\n";
            }
            i = min(i + windowSize, totalFrames), j = i;
        }
    }

    void simulate() {
        cout<<"Enter total number of frames to be sent: \n";
        cin>>totalFrames;
        cout<<"Enter window size: \n";
        cin>>windowSize;
        cout<<"Enter timeout interval: \n";
        cin>>timeoutInterval;

        sender();
    }
} sr;

int main() {

//    sw.simulate();
//    gbn.simulate();
    sr.simulate();

    return 0;
}
