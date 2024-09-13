帮助线程
i=0
while(i<num){
    for(j=0;(j<n)＆＆(i<num);j++,i++){
//帮助线程每访问B个热点数据之后与主线程进行一次同步
        for(l=0;(l<k)＆＆(i<num);l++,i++){
//在每组Ｋ和Ｐ操作中首先跳过Ｋ个热点数据, 然后推送Ｐ个热点数据
            address(data(i));
}
        for(m=0;(m<p)＆＆(i<num);m++,i++){
            address(data(i));
            prefetch(data(i));
        }
}
    sync;//同步
}