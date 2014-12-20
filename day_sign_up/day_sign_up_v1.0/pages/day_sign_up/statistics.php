<?php
/**
* statistics page
*/
$title = "SignUp statistics page";

$user = elgg_get_logged_in_user_entity();
$content ="<br/><div align = 'center'><h3>".$user->name.',你的签到记录如下</h3><hr />';
/*首先判断有没有登录*/
if($user->name)
{
	$content=$content."<table><tr><td>编号</td><td>签到时间</td></tr>";
	$guid = $user->guid;
	/*第二步判断今天有没有已经签到，避免重复*/
	$query = "SELECT sign_up_time from Elgg_daily_attendance where guid = {$guid}";
	$link = get_db_link('read');
	
	if(($ret = execute_query($query, $link)))
	{
		$i=1;
		//注意mysql_fetch_array与mysql_fetch_object()的区别
		while($sign_up_history = mysql_fetch_array($ret))
		{
			$show_str = $sign_up_history[0];
			$content = $content.'<tr><td>'.$i.'</td><td>'.$show_str.'</td></tr>';
			$i++;
		}
	}
	$content=$content."</table>";
}
else
{
	$content = elgg_echo("请先登录...");
}
$content = $content."</div>";
$vars = array( 'content' => $content, );
$body = elgg_view_layout('one_sidebar', $vars);
echo elgg_view_page($title, $body);
