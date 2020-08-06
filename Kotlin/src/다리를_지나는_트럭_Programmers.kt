import java.util.*

//https://programmers.co.kr/learn/courses/30/lessons/42583?language=kotlin

fun main(bridge_length: Int, weight: Int, truck_weights: IntArray): Int {
    var answer = 0

    val bridgeQueue: Queue<Int> = LinkedList(List(bridge_length) { 0 })
    val waitingQueue: Queue<Int> = LinkedList(truck_weights.toList())

    while (bridgeQueue.isNotEmpty()) {
        answer++
        bridgeQueue.poll()
        if (waitingQueue.isNotEmpty()) {
            if (bridgeQueue.sum() + waitingQueue.peek() <= weight)
                bridgeQueue.add(waitingQueue.poll())
            else
                bridgeQueue.add(0)
        }
    }
    return answer
}
