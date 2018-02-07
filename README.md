# no_excl_open


```
#!/bin/sh

LD_PRELOAD=/path/to/open_no_excl.so /usr/sbin/logrotate -s /var/lib/logrotate/logrotate.status /etc/logrotate.conf
EXITVALUE=$?
if [ $EXITVALUE != 0 ]; then
    /usr/bin/logger -t logrotate "ALERT exited abnormally with [$EXITVALUE]"
fi
exit 0
```

# これは何？

logrotateはrenameして新しいファイルをつくる。
都度ファイルを開いて書いて閉じるような朴訥なloggerの場合、logrotateがrenameして新しいログファイルを作成する間に、アプリケーションがログファイルをつくってしまうことがある。あるんです
logrotateは、新しいファイルを作る際に、O_EXCLを指定指定しているためファイルが存在するとエラーになる。
エラーになると、postscriptなども実行されてないので意図しない動作がうまれる。

/var/log/messagesに 

```
Jan 24 03:24:18 hostname logrotate: ALERT exited abnormally with [1]
```

やcronの失敗としてメールで


```
/etc/cron.daily/logrotate:

error: error creating output file /var/.../log: File exists
```

などという知らせが届く


no_excl_open はLD_PRELOADをつかって、ファイルを作成する際の O_EXCLを取り除いてみるもの

