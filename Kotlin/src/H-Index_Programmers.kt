import java.util.*

//https://programmers.co.kr/learn/courses/30/lessons/42747?language=kotlin
//C++로 풀었을 때 보다 훨씬 간단하게 풀 수 있었다.
fun solution(citations: IntArray): Int {
    var answer = 0

    for(i in 1 .. citations.size)
        if(citations.filter{ it >= i }.size > i) answer = i

    return answer
}