# Notices

Notification manager. Send notices to users via different methods.

## Sending messages from the pool

To send messages, need to add a task to Cron:

```
*/2 * * * * /usr/bin/drush --root=/home/user/domains/domain.com notices-email-send > /dev/null 2>&1
```
