# mod_limit_login_post_pass.c

## DESCRIPTION

 * .ftpaccess内で <Limit LOGIN> を有効にするモジュール
 * /etc/proftpd.confを編集できる権限をもたないユーザーにもログイン制限を与えたい場合に便利

## USAGE

 * /etc/proftpd.conf

 ```
LoadModule mod_limit_login_post_pass.c
```

 * $HOME/.ftpaccess

``` 
<Limit LOGIN>
    DenyAll
</Limit>
```

 * denied login is logged to /var/log/secure

``` 
Jan 27 18:14:56 *** proftpd[10219]: ***.***.jp (*.*.*.*[*.*.*.*]) - hoge: Limit access denies login.
Jan 27 18:14:56 *** proftpd[10219]: ***.***.jp (*.*.*.*[*.*.*.*]) - FTP session closed.
```

## INSTALL

dso-supported proftpd needed( ./configure --enabole-dso )

```
/path/to/proftpd/bin/prxs -c mod_limit_login_post_pass.c -i
```
