import java.util.*;
import java.math.*;
import java.io.*;

class Rational {
    BigInteger a, b;
    Rational(int _a, int _b) {
        a = BigInteger.valueOf(_a);
        b = BigInteger.valueOf(_b);
        reduce();
    }
    Rational(BigInteger _a, BigInteger _b) {
        a = _a;
        b = _b;
        reduce();
    }
    void reduce() {
        BigInteger d = a.gcd(b);
        a = a.divide(d); 
        b = b.divide(d);
    }
    Rational subtract(Rational t) {
        Rational res = new Rational(a.multiply(t.b).subtract(b.multiply(t.a)), b.multiply(t.b));
        res.reduce();
        return res;
    }
    Rational add(Rational t) {
        Rational res = new Rational(a.multiply(t.b).add(b.multiply(t.a)), b.multiply(t.b));
        res.reduce();
        return res;
    }
    Rational multiply(Rational t) {
        Rational res = new Rational(a.multiply(t.a), b.multiply(t.b));
        res.reduce();
        return res;
    }
}

public class Main implements Runnable {

    public static void main(String args[]) {
        new Main().run();
    }

    BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter writer;

    int T, P, M, K;
    Rational[][] mat;

    private void out(Rational x) {
        if (x.b.compareTo(BigInteger.ZERO) < 0) {
            x.b = x.b.multiply(BigInteger.valueOf(-1));
            x.a = x.a.multiply(BigInteger.valueOf(-1));
        }
        if (x.b.compareTo(BigInteger.valueOf(1)) == 0)
            System.out.print(x.a);
        else System.out.print(x.a + "/" + x.b);
    }

    private void buildMatrix() {
        for (int i = 0; i <= 400; ++i) {
            for (int j = 1; j <= i; ++j) {
                mat[i][j] = (new Rational(i, j + 1)).multiply(mat[i - 1][j - 1]); 
            }
            Rational tmp = new Rational(1, 1);
            for (int j = 1; j <= i; ++j)
                tmp = tmp.subtract(mat[i][j]);
            mat[i][0] = tmp;
        }
    }

    private void solve() throws Exception {
        T = nextInt();
        mat = new Rational[400 + 5][400 + 5];
        buildMatrix();
        for (int cas = 1; cas <= T; ++cas) {
            P = nextInt();
            M = nextInt();
            K = nextInt(); K--;
            System.out.print(P + " ");
            out(mat[M][K]);
            System.out.println();
        }
    }

    public void run() {
        try {

            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
            writer = new PrintWriter(System.out);
            solve();
            reader.close(); writer.close();

        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws Exception {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws Exception {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws Exception {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws Exception {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

}
