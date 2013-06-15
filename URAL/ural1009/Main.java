import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        (new Solver()).solve();
    }
}

class Solver {
    int N, K;
    long[] power, dp;
    void solve() {
        Scanner cin = new Scanner(System.in);
        N = cin.nextInt(); K = cin.nextInt();
        power = new long[N + 1];
        dp = new long[N + 1];
        power[0] = 1;
        for (int i = 1; i <= N; ++i)
            power[i] = power[i - 1] * K;
        dp[0] = 1; dp[1] = K - 1;
        for (int i = 2; i <= N; ++i) {
            dp[i] = (K - 1) * (dp[i - 1] + dp[i - 2]);
        }
        System.out.println(dp[N]);
    }
}


