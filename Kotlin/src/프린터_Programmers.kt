import java.util.*

//https://programmers.co.kr/learn/courses/30/lessons/42587?language=kotlin
fun main(priorities: IntArray, location: Int): Int {
    var answer = 0
    val printQueue = ArrayDeque<Pair<Int, Int>>()
    priorities.forEachIndexed { index, i -> printQueue.add(i to index) }

    while(printQueue.isNotEmpty()){
        var firstDoc = printQueue.poll()

        if(printQueue.filter { firstDoc.first < it.first }.size > 0){
            printQueue.add(firstDoc)
        } else {
            answer++
            if(firstDoc.second == location)
                return answer
        }
    }

    return answer
}