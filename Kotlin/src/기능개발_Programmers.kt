//https://programmers.co.kr/learn/courses/30/lessons/42586

fun main(progresses: IntArray, speeds: IntArray): IntArray {
    val answer: MutableList<Int> = arrayListOf()
    val days = progresses

    for (i in 0 until progresses.size) {
        days[i] = ((100 - progresses[i]) / speeds[i])
    }

    var max = days[0]
    var releaseCount = 1

    for (i in 1 until days.size) {
        if (max < days[i]) {
            answer.add(releaseCount)
            releaseCount = 1
            max = days[i]
        } else {
            releaseCount++
        }
    }

    answer.add(releaseCount)

    return answer.toIntArray()
}
