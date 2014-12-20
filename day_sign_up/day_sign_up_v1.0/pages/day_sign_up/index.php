<?php
$title = '签到';
$content="</br></br><div align='center'><h2> 今日签到排行榜</h2><hr /></div>";
//当日签到排行
//$now_time = strtotime(date('Y-m-d',time()));//零点时间
$now_time = date('Y-m-d',time());
$query = "SELECT username,name,sign_up_time from Elgg_daily_attendance x, Elgg_users_entity y where x.guid = y.guid and sign_up_time> ' $now_time' order by sign_up_time asc";
$link = get_db_link('read');

if(($ret = execute_query($query, $link)))
{
	$content=$content."<table border='1'><tr><td>序号</td><td>用户名</td><td>姓名</td><td>签到时间</td></tr>";
	$i=1;
	while($data = mysql_fetch_array($ret))
	{
		$content = $content."<tr><td>".$i."</td><td>".elgg_echo("%s",array($data[0]))."</td><td>".elgg_echo("%s",array($data[1]))."</td><td>".elgg_echo("%s",array($data[2]))."</td></tr>";
		$i++;
	}
	$content=$content."</table><hr />";
}

//历史签到次数统计
$content=$content."</br></br><div align='center'><h2> 签到次数排行榜</h2><hr /></div>";
$query = "SELECT username, name, count(id) as sum from Elgg_daily_attendance x, Elgg_users_entity y where x.guid = y.guid  group by username order by  sum desc";
$link = get_db_link('read');

if(($ret = execute_query($query, $link)))
{
	$content=$content."<table border='1'><tr><td>序号</td><td>用户名</td><td>姓名</td><td>签到次数</td></tr>";
	$i=1;
	while($data = mysql_fetch_array($ret))
	{
		$content = $content."<tr><td>".$i."</td><td>".elgg_echo("%s",array($data[0]))."</td><td>".elgg_echo("%s",array($data[1]))."</td><td>".elgg_echo("%s",array($data[2]))."</td></tr>";
		$i++;
	}
	$content=$content."</table><hr />";
}
//show in pages
$vars = array( 'content' => $content, );
$body = elgg_view_layout('one_sidebar', $vars);
echo elgg_view_page($title, $body);
