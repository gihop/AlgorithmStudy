//https://programmers.co.kr/learn/courses/30/lessons/42578?language=kotlin

//이 문제의 답은 의상의 종류가 세가지, 예를 들어 모자, 상의, 하의일 때,
//모자가 2가지, 상의가 3가지, 하의가 1가지라면,
//각 의상의 가짓수+1(안입은 경우까지 포함하여), (3 * 4 * 2)의 -1이 답이다.
//groupBy는 it[1] 즉, 의상의 종류를 키로 map형태로 반환이 된다.
//즉 상의가 2벌이라면, 상의:[빨간옷, 하얀옷] 형태로 저장되고, 하의가 2번이면, 하의:[흰 바지, 검은 바지] 형태로 저장된다.
//여기서 values 프로퍼티를 사용하면 [[빨간옷, 하얀옷], [흰 바지, 검은 바지]] 형태로 반환이 되고,
//keys 프로퍼티를 사용하면 [상의, 하의] 형태로 반환된다.
//fold 함수로 초깃값을 1로 설정하고 values의 반환되는 리스트의 사이즈를 곱해서 답을 구한다.
fun solution(clothes: Array<Array<String>>): Int {
    return clothes.groupBy { it[1] }.values.fold(1) { result, list -> result * (list.size + 1) } - 1
}