# kube-ps1
C program to parse your kubeconfig and display current context on PS1

## Dependencies


| Name | Version |
|--|--|
| libcyaml | [v1.3.1](https://github.com/tlsa/libcyaml/tree/v1.3.1) |

## Example
```console
$ export PS1="\[\e[34;01m\]\u\[\e[0m\]@\h\[\e[0;01m\] \w [\$(kube-ps1 $HOME/.kube/config)]\n$ \[\e[0m\]"
joao@archlinux ~ [prod-k8s|ingress]
$ 
```
