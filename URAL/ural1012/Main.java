import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) throws IOException {
        (new Solver()).solve();
    }
}

class Solver {
    InputReader in;
    PrintWriter out;
    int N, K;
    BigInteger[] power, dp;
    BigInteger val(int x) {
        return BigInteger.valueOf(x);
    }
    void calc() {
        power = new BigInteger[N + 1];
        dp = new BigInteger[N + 1];
        power[0] = val(1);
        for (int i = 1; i <= N; ++i)
            power[i] = power[i - 1].multiply(val(K));
        dp[0] = val(1); dp[1] = val(K - 1);
        for (int i = 2; i <= N; ++i) {
            dp[i] = val(K - 1).multiply(dp[i - 1].add(dp[i - 2]));
        }
        out.println(dp[N]);
    }
    void solve() throws IOException {
        in = new InputReader(System.in);
        out = new PrintWriter(System.out);
        N = in.nextInt();
        K = in.nextInt();
        calc();
        in.close();
        out.close();
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;
    InputReader(InputStream in) throws IOException {
        reader = new BufferedReader(new InputStreamReader(in));
        tokenizer = new StringTokenizer("");
    }
    String nextToken() throws IOException {
        while (!tokenizer.hasMoreTokens()) 
            tokenizer = new StringTokenizer(reader.readLine());
        return tokenizer.nextToken();
    }
    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
    void close() throws IOException {
        reader.close();
    }
}
