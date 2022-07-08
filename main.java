import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Solution {
	private static BufferedReader br;
	private static UserSolution usersolution = new UserSolution();

	private final static int INIT = 100;
	private final static int ADD_RESTAURANT = 200;
	private final static int REMOVE_RESTAURANT = 300;
	private final static int ORDER = 400;
	private final static int BE_FRIEND = 500;
	private final static int RECOMMEND = 600;

	private static boolean run() throws Exception {
		int px[] = new int[30];
		int py[] = new int[30];

		StringTokenizer stdin = new StringTokenizer(br.readLine(), " ");

		int query_num = Integer.parseInt(stdin.nextToken());
		int n = 0;

		boolean ok = false;

		for (int i = 0; i < query_num; i++) {
			stdin = new StringTokenizer(br.readLine(), " ");

			int query = Integer.parseInt(stdin.nextToken());

			if (query == INIT) {

				n = Integer.parseInt(stdin.nextToken());
				stdin = new StringTokenizer(br.readLine(), " ");
				for (int j = 0; j < n; j++)
					px[j] = Integer.parseInt(stdin.nextToken());
				stdin = new StringTokenizer(br.readLine(), " ");
				for (int j = 0; j < n; j++)
					py[j] = Integer.parseInt(stdin.nextToken());

				usersolution.init(n, px, py);
				ok = true;
			} else if (query == ADD_RESTAURANT) {
				int pID, x, y;
				pID = Integer.parseInt(stdin.nextToken());
				x = Integer.parseInt(stdin.nextToken());
				y = Integer.parseInt(stdin.nextToken());

				usersolution.addRestaurant(pID, x, y);
			} else if (query == REMOVE_RESTAURANT) {
				int pID;
				pID = Integer.parseInt(stdin.nextToken());

				usersolution.removeRestaurant(pID);
			} else if (query == ORDER) {
				int uID, pID;
				uID = Integer.parseInt(stdin.nextToken());
				pID = Integer.parseInt(stdin.nextToken());
				
				usersolution.order(uID, pID);
			} else if (query == BE_FRIEND) {
				int uID1, uID2;
				uID1 = Integer.parseInt(stdin.nextToken());
				uID2 = Integer.parseInt(stdin.nextToken());
				
				usersolution.beFriend(uID1, uID2);
			} else if (query == RECOMMEND) {

				int uID;
				uID = Integer.parseInt(stdin.nextToken());
				
				int ret = usersolution.recommend(uID);
				int ans = Integer.parseInt(stdin.nextToken());
				if (ret != ans)
					ok = false;
			}
		}

		return ok;
	}

	public static void main(String[] args) throws Exception {
		int T, MARK;

		//System.setIn(new java.io.FileInputStream("res/sample_input.txt"));
		br = new BufferedReader(new InputStreamReader(System.in));

		StringTokenizer stinit = new StringTokenizer(br.readLine(), " ");
		T = Integer.parseInt(stinit.nextToken());
		MARK = Integer.parseInt(stinit.nextToken());

		for (int tc = 1; tc <= T; tc++) {
			int score = run() ? MARK : 0;
			System.out.println("#" + tc + " " + score);
		}

		br.close();
	}
}
