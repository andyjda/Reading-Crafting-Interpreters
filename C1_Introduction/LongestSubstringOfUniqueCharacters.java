import java.util.HashMap;
import java.util.Map;

/*
  Given a string s, find the length of the longest substring
  without repeating characters.

  Leetcode link:
  https://leetcode.com/problems/longest-substring-without-repeating-characters/

  @author Andrew De Angelis
 */
public class LongestSubstringOfUniqueCharacters {

    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_WHITE = "\u001B[37m";


    public static void main(String[] args) {
	System.out.println(ANSI_WHITE +
			   "welcome to LongestSubstringOfUniqueCharacters!");
	// a query = string to inspect, and its expected result
	String[][] queries = {{"abba", "2"},
			      {"qwertyuiopabbaqwertyuiop", "12"},
			      {"abcabcbb", "3"},
			      {"bbbbb", "1"},
			      {"pwwkew", "3"}};
        for (String[] q : queries) {
	    callIt(q);   
	}
    }

    public static void callIt(String[] q) {
	String s = q[0];
        int expected = Integer.valueOf(q[1]);
	System.out.println(ANSI_WHITE + "\ncalling find(s) with s: " + s);
	int res = find(s);
	System.out.print("got res:  " + res);
	if (res == expected) {
	    System.out.println(ANSI_GREEN + "\tsuccess");
	} else {
	    System.out.println(ANSI_RED + "\tfailed!");
	    System.out.println("expected: " + expected + "\n");
	}
    }

    public static int find(String s) {
	Map<Character, Integer> previouslySeen = new HashMap<>();
	int maxLen = 0;
	int curLen = 0;
	int startPoint = 0;
	for (int i = 0; i < s.length(); i++) {
	    char c = s.charAt(i);
	    Integer lastSeenAt = previouslySeen.get(c);
	    if (lastSeenAt == null) {
		lastSeenAt = -1;
	    }
	    if (lastSeenAt >= startPoint) {
		startPoint = lastSeenAt + 1;
		curLen = i - lastSeenAt;
	    } else {
		curLen++;
		if (maxLen < curLen) {
		    maxLen = curLen;
		}
	    }

	    previouslySeen.put(c, i);
	}
	return maxLen;
    }

    
}
